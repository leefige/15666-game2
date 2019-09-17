#include "StoryMode.hpp"

#include "Sprite.hpp"
#include "DrawSprites.hpp"
#include "Load.hpp"
#include "data_path.hpp"
#include "gl_errors.hpp"
#include "Sound.hpp"

#include <algorithm>
#include <random>

Sprite const *sprite_bg = nullptr;
Sprite const *sprite_flag = nullptr;
Sprite const *sprite_point = nullptr;
Sprite const *sprite_bomb = nullptr;

const std::string text_bomb = "BOMB!";
const std::string text_pass = "PASS!";

extern Load< Sound::Sample > sound_clicks[110];

Load< Sound::Sample > sound_clonk(LoadTagDefault, []() -> Sound::Sample *{
	std::vector< float > data(size_t(48000 * 0.2f), 0.0f);
	for (uint32_t i = 0; i < data.size(); ++i) {
		float t = i / float(48000);
		//phase-modulated sine wave (creates some metal-like sound):
		data[i] = std::sin(3.1415926f * 2.0f * 220.0f * t + std::sin(3.1415926f * 2.0f * 200.0f * t));
		//quadratic falloff:
		data[i] *= 0.3f * std::pow(std::max(0.0f, (1.0f - t / 0.2f)), 2.0f);
	}
	return new Sound::Sample(data);
});

Load< SpriteAtlas > sprites(LoadTagDefault, []() -> SpriteAtlas const * {
	SpriteAtlas const *ret = new SpriteAtlas(data_path("mine"));

	sprite_bg = &ret->lookup("bg");
	sprite_flag = &ret->lookup("flag");
	sprite_point = &ret->lookup("point");
	sprite_bomb = &ret->lookup("bomb");

	return ret;
});

StoryMode::StoryMode() {
	mine_pos.x = float(rand() % 200 + 30);
	mine_pos.y = float(rand() % 180 + 25);
}

StoryMode::~StoryMode() {
}

void StoryMode::echo(int x, int y) {
	float gap = 10.0f * 10.0f;
	explore.emplace_back(x, y);
	point_decay.push_back(0);
	glm::vec2 dif = glm::vec2(x, y) - this->mine_pos;
    float dist_sq = dif.x * dif.x + dif.y * dif.y;
    int level = std::min(int(dist_sq / gap), 109);
	point_music.push_back(Sound::play(*sound_clicks[level]));
}

void StoryMode::set_flag(int x, int y) {
	if (flag_pos.x < 0 && flag_pos.y < 0) {
		flag_pos = glm::vec2(x, y);
		Sound::play(*sound_clonk);
	} else {
		auto dif = flag_pos - glm::vec2(x,y);
		// clean flag
		if (dif.x * dif.x + dif.y * dif.y <= radius * radius) {
			flag_pos = glm::vec2(-1, -1);
			Sound::play(*sound_clonk);
		}
	}
}

bool StoryMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_RETURN) {
			if (flag_pos.x >= 0 && flag_pos.y >= 0) {
				auto dif = flag_pos - mine_pos;
				if (dif.x * dif.x + dif.y * dif.y <= radius * radius) {
					// success
					game_state = pass;
				} else {
					game_state = bomb;
				}
			}
		} else if (evt.key.keysym.sym == SDLK_ESCAPE && game_state != gaming) {
			// restart
			mine_pos.x = float(rand() % 200 + 30);
			mine_pos.y = float(rand() % 180 + 25);
			flag_pos = glm::vec2(-1, -1);
			explore.clear();
			point_decay.clear();
			point_music.clear();
			game_state = gaming;
		}
	} else if (evt.type == SDL_MOUSEBUTTONDOWN) {
		// mouse pos
        int x = int(evt.motion.x / 2);
        int y = int(view_max.y - evt.motion.y / 2);

		if (evt.button.button == SDL_BUTTON_LEFT) {
			echo(x, y);
		} else if (evt.button.button == SDL_BUTTON_RIGHT) {
			set_flag(x, y);
		}
	}
	return false;
}

void StoryMode::update(float elapsed) {
	int pop_cnt = 0;
	// pop all stopped echoes
	for (int i = 0; i < point_music.size(); i++) {
		auto pm = point_music[i];
		if (pm->stopped) {
			pop_cnt++;
		}
		point_decay[i]++;
	}
	for (; pop_cnt > 0; pop_cnt--) {
		point_music.pop_front();
		point_decay.pop_front();
		explore.pop_front();
	}
}

void StoryMode::draw(glm::uvec2 const &drawable_size) {
	
	//clear the color buffer:
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//use alpha blending:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//don't use the depth test:
	glDisable(GL_DEPTH_TEST);

	{ //use a DrawSprites to do the drawing:
		glm::vec2 at(30.0f, view_max.y - 60.0f);
		DrawSprites draw(*sprites, view_min, view_max, drawable_size, DrawSprites::AlignPixelPerfect);
		glm::vec2 ul = glm::vec2(view_min.x, view_max.y);

		draw.draw(*sprite_bg, ul);

		// draw echoes
		for (int i = 0; i < explore.size(); i++) {
			auto echo = explore[i];
			draw.draw(*sprite_point, echo, 1.0f, glm::u8vec4(0xff, 0xff, 0xff, 0xff * std::pow(0.9, point_decay[i])));
		}

		// draw flag
		if (flag_pos.x > 0 && flag_pos.y > 0) {
			draw.draw(*sprite_flag, flag_pos);
		}

		// draw results
		if (game_state == bomb) {
			draw.draw_text(
				text_bomb, at, 5, glm::u8vec4(0x99, 0x11, 0x11, 0xff)
			);
			draw.draw(*sprite_bomb, mine_pos);
		} else if (game_state == pass) {
			draw.draw_text(
				text_pass, at, 5, glm::u8vec4(0x11, 0x99, 0x11, 0xff)
			);
		}
	}
	GL_ERRORS(); //did the DrawSprites do something wrong?
}
