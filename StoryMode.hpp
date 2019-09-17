
/*
 * StoryMode implements a story about The Planet of Choices.
 *
 */

#include "Mode.hpp"
#include "Sound.hpp"
#include <deque>

struct StoryMode : Mode {
	StoryMode();
	virtual ~StoryMode();

	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	// internal ----------------------
	void echo(int x, int y);
	void set_flag(int x, int y);

	glm::vec2 view_min = glm::vec2(0, 0);
	glm::vec2 view_max = glm::vec2(256, 224);

	float text_height = 12;
	float choice_height = text_height;

	glm::vec2 mine_pos;
	glm::vec2 flag_pos = glm::vec2(-1, -1);
	std::deque<glm::vec2> explore;
	std::deque<int> point_decay;
	std::deque<std::shared_ptr<Sound::PlayingSample> > point_music;

	const int func_cnt = 50;
	Sound::Sample *(*funcs[50])();
	Sound::Sample *StoryMode::get_sound_click(int x, int y);

	float radius = 12;

	enum {
		pass,
		bomb,
		gaming
	} game_state = gaming;
};
