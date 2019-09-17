/*
 * Description: 
 * Created Date: 2019-09-17
 * Author: Yifei Li (yifeili3) - CMU
 * -----
 * Last Modified: 2019-09-17
 * Modified By: Yifei Li (yifeili3)
 * -----
 * Copyright (c) 2019
 */
#include <cmath>
#include <algorithm>

#include "Load.hpp"
#include "data_path.hpp"
#include "gl_errors.hpp"
#include "Sound.hpp"

auto find_pitch = [](float origin, int level) -> float {
    const float gap = (float)std::pow(2, 1.0 / 12); 
    origin *= pow(gap, level);
    return origin;
};

auto gen_sound = [](int level) -> Sound::Sample *{float standard_A = 440.0f;
    float pitch = std::max(standard_A / 4, find_pitch(standard_A * 4, level));
    std::vector< float > data(size_t(48000 * 0.2f), 0.0f);
    for (uint32_t i = 0; i < data.size(); ++i) {
        float t = i / float(48000);
        //phase-modulated sine wave (creates some metal-like sound):
        data[i] = std::sin(3.1415926f * 2.0f * pitch * t + std::sin(3.1415926f * 2.0f * 450.0f * t));
        //quadratic falloff:
        data[i] *= 0.3f * std::pow(std::max(0.0f, (1.0f - t / 0.2f)), 2.0f);
    }
    return new Sound::Sample(data);
};

Load< Sound::Sample > sound_clicks[110] = {
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(0);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-1);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-2);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-3);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-4);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-5);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-6);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-7);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-8);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-9);}),

    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-10);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-11);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-12);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-13);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-14);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-15);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-16);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-17);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-18);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-19);}),

    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-20);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-21);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-22);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-23);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-24);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-25);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-26);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-27);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-28);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-29);}),

    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-30);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-31);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-32);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-33);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-34);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-35);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-36);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-37);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-38);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-39);}),

    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-40);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-41);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-42);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-43);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-44);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-45);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-46);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-47);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-48);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-49);}),

    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-50);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-51);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-52);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-53);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-54);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-55);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-56);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-57);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-58);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-59);}),

	
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-60);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-61);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-62);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-63);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-64);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-65);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-66);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-67);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-68);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-69);}),

	
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-70);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-71);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-72);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-73);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-74);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-75);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-76);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-77);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-78);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-79);}),

	
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-80);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-81);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-82);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-83);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-84);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-85);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-86);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-87);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-88);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-89);}),

	
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-90);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-91);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-92);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-93);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-94);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-95);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-96);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-97);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-98);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-99);}),

	
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-100);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-101);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-102);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-103);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-104);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-105);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-106);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-107);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-108);}),
    Load< Sound::Sample > (LoadTagDefault, []() -> Sound::Sample *{return gen_sound(-109);})
};