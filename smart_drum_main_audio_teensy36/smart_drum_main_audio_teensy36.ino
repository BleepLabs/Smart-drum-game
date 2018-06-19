#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>
#include <FastLED.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform8;      //xy=87,496
AudioSynthWaveform       waveform9;      //xy=100,538
AudioSynthWaveform       waveform4;      //xy=101,303
AudioSynthWaveform       waveform6;      //xy=111,405
AudioSynthWaveform       waveform7;      //xy=122,452
AudioSynthWaveform       waveform5;      //xy=124,355
AudioSynthWaveform       waveform15;     //xy=123,777
AudioSynthWaveform       waveform10;     //xy=125,593
AudioSynthWaveform       waveform16;     //xy=128,817
AudioSynthWaveform       waveform3;      //xy=131,267
AudioSynthWaveform       waveform12;     //xy=134,661
AudioSynthWaveform       waveform13;     //xy=140,705
AudioSynthWaveform       waveform11;     //xy=144,625
AudioSynthWaveform       waveform14;     //xy=146,746
AudioSynthWaveform       waveform2;      //xy=171,228
AudioSynthWaveform       waveform17;     //xy=202,879
AudioSynthWaveform       waveform1;      //xy=206,194
AudioSynthWaveform       waveform18;     //xy=204,926
AudioMixer4              mixer1;         //xy=408,264
AudioMixer4              mixer5;         //xy=412,541
AudioMixer4              mixer3;         //xy=415,345
AudioMixer4              mixer4;         //xy=418,462
AudioSynthWaveform       waveform19;     //xy=439,804
AudioSynthWaveform       waveform20;     //xy=453,843
AudioMixer4              mixer2;         //xy=587,369
AudioMixer4              mixer7;         //xy=590,527
AudioSynthSimpleDrum     drum1;          //xy=593,608
AudioMixer4              mixer6;         //xy=729,433
AudioAnalyzePeak         peak1;          //xy=814,298
AudioOutputI2S           i2s1;           //xy=853,364
AudioConnection          patchCord1(waveform8, 0, mixer3, 3);
AudioConnection          patchCord2(waveform9, 0, mixer4, 0);
AudioConnection          patchCord3(waveform4, 0, mixer1, 3);
AudioConnection          patchCord4(waveform6, 0, mixer3, 1);
AudioConnection          patchCord5(waveform7, 0, mixer3, 2);
AudioConnection          patchCord6(waveform5, 0, mixer3, 0);
AudioConnection          patchCord7(waveform15, 0, mixer5, 2);
AudioConnection          patchCord8(waveform10, 0, mixer4, 1);
AudioConnection          patchCord9(waveform16, 0, mixer5, 3);
AudioConnection          patchCord10(waveform3, 0, mixer1, 2);
AudioConnection          patchCord11(waveform12, 0, mixer4, 3);
AudioConnection          patchCord12(waveform13, 0, mixer5, 0);
AudioConnection          patchCord13(waveform11, 0, mixer4, 2);
AudioConnection          patchCord14(waveform14, 0, mixer5, 1);
AudioConnection          patchCord15(waveform2, 0, mixer1, 1);
AudioConnection          patchCord16(waveform17, 0, mixer7, 0);
AudioConnection          patchCord17(waveform1, 0, mixer1, 0);
AudioConnection          patchCord18(waveform18, 0, mixer7, 1);
AudioConnection          patchCord19(mixer1, 0, mixer2, 0);
AudioConnection          patchCord20(mixer5, 0, mixer2, 3);
AudioConnection          patchCord21(mixer3, 0, mixer2, 1);
AudioConnection          patchCord22(mixer4, 0, mixer2, 2);
AudioConnection          patchCord23(waveform19, 0, mixer7, 2);
AudioConnection          patchCord24(waveform20, 0, mixer7, 3);
AudioConnection          patchCord25(mixer2, 0, mixer6, 0);
AudioConnection          patchCord26(mixer7, 0, mixer6, 1);
AudioConnection          patchCord27(drum1, 0, mixer6, 2);
AudioConnection          patchCord28(mixer6, 0, i2s1, 1);
AudioConnection          patchCord29(mixer6, 0, i2s1, 0);
AudioConnection          patchCord30(mixer6, peak1);
AudioControlSGTL5000     sgtl5000_1;     //xy=399,146
// GUItool: end automatically generated code


#define FLASH_CS_PIN    6    //These three are necessary to read the flash chip 
#define FLASH_MOSI_PIN  7
#define FLASH_SCK_PIN   14
#define BUTT_NUM 9
#define MAX_PLAYING 8
#define SEQ_LEN 32


#define PLAYBACK_MODE 1
#define WAIT_AFTER_PLAY_MODE 2
#define LISTEN_MODE 3
#define DISPLAY_SCORE 4
#define STOP_MODE 5
#define GET_READY 6
#define BUTTON_WAIT 7
#define PRE_PLAYBACK_MODE 8

#define LISTEN 0
#define OKAY 1
#define PRESS 2
#define BUTTON 3
#define READY 4
#define COOL 5
#define GREAT 6
#define WOW 7
#define SCORE 8
#define LEVEL 9
#define FINAL 10
#define GO 11
#define TWO_PLAY 12
#define ONE_PLAY 13
#define ARROW 14
#define QUESTION_MARK 15

byte players, player_num, player_sel;
byte button_pins[4][BUTT_NUM] = {
  {24, 25, 26, 27, 28, 29, 30, 31, 32},
  {33, 34, 35, 36, 37, 38, 39, 15, 16},
};
byte control_button_pins[4] = {
  3, 4, 5
};
byte ctrl_reading[BUTT_NUM];
byte prev_ctrl_reading[BUTT_NUM];

byte button_led_pins[3][BUTT_NUM] = {2, 3, 4, 5};
byte score_lock[3][BUTT_NUM];
byte button_led_state[3][BUTT_NUM];
byte button_led_output[3][BUTT_NUM];
byte sample_trigger[3][BUTT_NUM];
byte button_pressed[3][BUTT_NUM];
float freq[8];
byte button_reading[3][BUTT_NUM];
byte prev_button_reading[3][BUTT_NUM];
uint32_t cm, prev[20];
byte num_playing;
byte num_check_count;
float peak1_read;
byte major_mode;
byte seq_mode;
byte any_button_pressed;
byte score[3];
byte seq_exit;
byte timeout, countdown;
uint32_t time_since_pressed;
byte wait_button_once[3];
byte score_inc;
uint16_t seq_count, LISTEN_MODE_count;
uint16_t seq_rate = 130;
byte last_button;
byte midionce, lvl;
byte full_score[3];
byte ready_count;
byte player_in[3];
float drum_freq[3] = {1174.659227, 1046.502399, 880.0001162};
byte difficulty;
byte easy_speed = 130;
byte hard_speed = 120;

//difficulty, num of seq, sounds, length
byte sequences[2][6][9][SEQ_LEN] = {
  {
    {
      {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {1, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 1,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  1, 0, 1, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {1, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    }

  },

  {
    {
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 1, 0,  1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 1, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 1, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {1, 0, 0, 1,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 1,  0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0} //hi
    },
    {
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 1, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,   0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {0, 0, 1, 0,  1, 0, 1, 0,  0, 0, 1, 0,  1, 0, 1, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //kick
      {1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    },
    {
      {1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,   1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //kick
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //snare
      {0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0,  1, 0, 0, 1,   0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clap
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //cow
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //clave
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0}, //cym
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //fx
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}, //low
      {0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0} //hi
    }

  }
};



#define NUM_LEDS 255

CRGB leds[NUM_LEDS];

void setup() {


  AudioNoInterrupts(); //turn off the audio library so we can set things up

  AudioMemory(100);

  FastLED.addLeds<WS2812B, 2, RGB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( 255 );

  MIDI.begin(MIDI_CHANNEL_OMNI);

  for (int i = 0; i < BUTT_NUM; i++)
  {
    pinMode(button_pins[0][i], INPUT_PULLUP);
    pinMode(button_pins[1][i], INPUT_PULLUP);

    pinMode(button_led_pins[0][i], OUTPUT);
    pinMode(button_led_pins[1][i], OUTPUT);
  }

  for (int i = 0; i < 3; i++)
  {
    pinMode(control_button_pins[i], INPUT_PULLUP);
  }

  SPI.setMOSI(FLASH_MOSI_PIN);   //These three are necessary to read the flash chip
  SPI.setSCK(FLASH_SCK_PIN);
  SerialFlash.begin(FLASH_CS_PIN);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  drum1.frequency(drum_freq[0]);
  drum1.length(40);
  drum1.pitchMod(.45);

  freq[1] = 86.1679 * 2;

  waveform1.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform1.sample_begin(756736, 9978);  //kick1

  waveform2.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform2.sample_begin(32768, 8708); //snare1

  waveform3.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform3.sample_begin(556800, 9518);  //clap1

  waveform4.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform4.sample_begin(589056, 4266); //cow1

  waveform5.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform5.sample_begin(576000, 6459); //clave1

  waveform6.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform6.sample_begin(597760, 37196); //cym1

  waveform7.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform7.sample_begin(672256, 30863); //fx1

  waveform8.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform8.sample_begin(78336, 20391); //low1

  waveform9.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform9.sample_begin(50432, 13952); //high1


  waveform10.begin(1, freq[1] * 1.5, SERIAL_FLASH_SAMPLE);
  waveform10.sample_begin(328192, 74142); //kick2

  waveform11.begin(1, freq[1] * 2, SERIAL_FLASH_SAMPLE);
  waveform11.sample_begin(476672, 19516); //snare2

  waveform12.begin(1, freq[1] * 2, SERIAL_FLASH_SAMPLE);
  waveform12.sample_begin(776704, 21675);  //clap2

  waveform13.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform13.sample_begin(589056, 4266); //cow2

  waveform14.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform14.sample_begin(820224, 9109); //clave2

  waveform15.begin(1, freq[1] * 2, SERIAL_FLASH_SAMPLE);
  waveform15.sample_begin(119296, 66916); //cym2

  waveform16.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform16.sample_begin(253184, 20904); //fx2

  waveform17.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform17.sample_begin(902144, 37481); //low2

  waveform18.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform18.sample_begin(515840, 20412); //high1



  waveform19.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform19.sample_begin(734208, 11209); //hat1

  waveform20.begin(1, freq[1], SERIAL_FLASH_SAMPLE);
  waveform20.sample_begin(295168, 16480); //hat1


  float amp1 = 1.00 / 3.00;
  mixer1.gain(0, amp1);
  mixer1.gain(1, amp1);
  mixer1.gain(2, amp1);
  mixer1.gain(3, amp1);

  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 1);

  mixer3.gain(0, amp1);
  mixer3.gain(1, amp1);
  mixer3.gain(2, amp1);
  mixer3.gain(3, amp1);

  mixer4.gain(0, amp1);
  mixer4.gain(1, amp1);
  mixer4.gain(2, amp1);
  mixer4.gain(3, amp1);

  mixer5.gain(0, amp1);
  mixer5.gain(1, amp1);
  mixer5.gain(2, amp1);
  mixer5.gain(3, amp1);

  mixer6.gain(0, 1);
  mixer6.gain(1, 1);
  mixer6.gain(2, amp1);
  mixer6.gain(3, 0);

  mixer7.gain(0, amp1);
  mixer7.gain(1, amp1);
  mixer7.gain(2, amp1);
  mixer7.gain(3, amp1);


  major_mode = 0;
  lvl = 0;
  seq_mode = BUTTON_WAIT;
  player_num = 0;
  player_sel = 0;

  for (int ledw = 0; ledw < BUTT_NUM; ledw++) {

    byte led_sat = 255;
    if (ledw == 4) {
      led_sat = 0;
    }
    for (int j = 0; j < 12; j++) {
      leds[(ledw * 12) + j] = CHSV(ledw * 28, led_sat, 12);
    }
  }

  analogReadAveraging(21);
  AudioInterrupts();

}

byte ledj;
void loop() {

  cm = millis();

  /*
    if (cm - time_since_pressed > 45000 && major_mode == 1) {
      major_mode = 0;
      MIDI.sendControlChange(3, 0, 1);
      MIDI.sendControlChange(3, 0, 2);

      Serial.println("t i m e o u t");
    //AudioNoInterrupts();
    //delay(1000);
    //AudioInterrupts();
    }
  */
  if (major_mode == 0) {

    seq_rate = easy_speed;
    seq_count = 0;
    countdown = 0;
    seq_exit = 0;
    midionce = 0;
    any_button_pressed = 0;
    ready_count = 0;
    player_sel = 0;
    wait_button_once[0] = 0;
    wait_button_once[1] = 0;
    difficulty = 0;
    full_score[0] = 0;
    full_score[1] = 0;
    drum1.frequency(1200);

    if (cm - prev[5] > 1000) {
      prev[5] = cm;
      MIDI.sendControlChange(3, 0, 1);
      MIDI.sendControlChange(3, 0, 2);
    }
  }

  if (cm - prev[6] > 4) {
    prev[6] = cm;
    float vol1 = (analogRead(A3) / (2.5 * 1023.00)) + .4;
    sgtl5000_1.volume(vol1);
    // Serial.println(vol1);

  }


  if (cm - prev[1] > 40) {
    prev[1] = cm;
    ledj += 16;
    for (int m = 0; m < NUM_LEDS; m++) {
      // leds[m] = CHSV( m*12 , 255, 255);
    }
    for (int j = 0; j < 12; j++) {

      if (major_mode == 0) {
        leds[(18 * 12) + j] = CHSV( 200 + random(50) , 200 - random(50), 255);
        leds[(19 * 12) + j] = CHSV(0, 0, 0);
        leds[(20 * 12) + j] = CHSV( 0 , 0, 0);

      }
      if (major_mode == 1) {
        if (difficulty == 0) {

          leds[(19 * 12) + j] = CHSV( 85 + random(10) , 200 + random(10), 255);
          leds[(18 * 12) + j] = CHSV(0, 0, 0);
          leds[(20 * 12) + j] = CHSV( 0 , 0, 0);
        }
        if (difficulty == 1) {
          leds[(20 * 12) + j] = CHSV( 0 + random(10) , 200 + random(10), 255);
          leds[(18 * 12) + j] = CHSV(0, 0, 0);
          leds[(19 * 12) + j] = CHSV( 0 , 0, 0);
        }
      }
    }
    FastLED.show();

  }

  if (cm - prev[2] > 5) {
    prev[2] = cm;

    for (int cl = 0; cl < BUTT_NUM; cl++) {
      button_pressed[0][cl] = 0;
      button_pressed[1][cl] = 0;
    }


    for (int cr = 0; cr < 3; cr++) {
      prev_ctrl_reading[cr] = ctrl_reading[cr];
      ctrl_reading[cr] = digitalRead(control_button_pins[cr]);
    }

    if (ctrl_reading[0] == 0 && prev_ctrl_reading[0] == 1) {
      major_mode = 0;
      seq_mode = BUTTON_WAIT;
      full_score[0] = 0;
      full_score[1] = 0;
    }

    if (ctrl_reading[1] == 0 && prev_ctrl_reading[1] == 1) {
      major_mode = 1;
      lvl = 0;
      difficulty = 0;
      seq_rate = easy_speed;
      seq_mode = BUTTON_WAIT;
      full_score[0] = 0;
      full_score[1] = 0;
    }

    if (ctrl_reading[2] == 0 && prev_ctrl_reading[2] == 1) {
      major_mode = 1;
      lvl = 0;
      difficulty = 1;
      seq_rate = hard_speed;
      seq_mode = BUTTON_WAIT;
      full_score[0] = 0;
      full_score[1] = 0;
    }





    for (int br = 0; br < BUTT_NUM; br++) {
      for (int ps = 0; ps < 2; ps++) {
        prev_button_reading[ps][br] = button_reading[ps][br];
        button_reading[ps][br] = digitalRead(button_pins[ps][br]);

        if (button_reading[ps][br] == 0 && prev_button_reading[ps][br] == 1) {


          any_button_pressed = ps + 1;
          //Serial.rint("b ");
          //Serial.rint(ps);
          //Serial.rint(" ");
          //Serial.rintln(br);
          time_since_pressed = cm;
          button_led_state[ps][br] = 1;
          button_led_output[ps][br] = 255;
          sample_trigger[ps][br] = 1;
          button_pressed[ps][br] = 1;
          last_button = br;
          MIDI.sendNoteOn(last_button, 0 , ps + 1);


          if (seq_mode == LISTEN_MODE)
          {
            byte nsc = seq_count + 1 % SEQ_LEN;
            byte psc = seq_count - 1;
            if (psc < 0) {
              psc += SEQ_LEN;
            }
            //score_lock[br] = 0;

            if (button_pressed[ps][br] == 1) {
              if (sequences[difficulty][lvl][br][psc] == 1) {
                if (score_lock[ps][br] == 0) {
                  score[ps] += 1;
                  //Serial.rintln("+");
                  button_pressed[ps][br] = 0;
                  score_lock[ps][br] = 1;
                }
              }

              if (sequences[difficulty][lvl][br][seq_count] == 1) {
                if (score_lock[ps][br] == 0) {
                  score[ps] += 2;
                  //Serial.rintln("+++");
                  button_pressed[ps][br] = 0;
                  score_lock[ps][br] = 1;
                }
              }

              if (sequences[difficulty][lvl][br][nsc] == 1) {
                if (score_lock[ps][br] == 0) {
                  score[ps] += 1;
                  //Serial.rintln("+");
                  button_pressed[ps][br] = 0;
                  score_lock[ps][br] = 1;
                }
              }

            }
          }
        }
      }
    }

    for (int ledw = 0; ledw < BUTT_NUM; ledw++) {

      byte led_sat = 255;
      if (ledw == 4) {
        led_sat = 0;
      }
      for (int j = 0; j < 12; j++) {
        leds[(ledw * 12) + j] = CHSV(ledw * 28, led_sat, button_led_output[0][ledw]);
        //leds[(ledw*12) + (9*12) + j] = CHSV(ledw * 28, led_sat, button_led_output[1][ledw]);
      }

      for (int ps = 0; ps < 2; ps++) {
        //byte ps = 0;


        if (button_led_state[ps][ledw] == 1) {
          button_led_output[ps][ledw] *= .98;
          //button_led_output[ledw] = peak1_read;
          if (button_led_output[ps][ledw] < 12) {
            button_led_output[ps][ledw] = 12;
            button_led_state[ps][ledw] = 12;
          }
        }

      }
    }
  }


  if (cm - prev[3] > 2 ) {
    prev[3] = cm;

    check_playing();

    if (sample_trigger[0][0] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform1.sample_play();
        check_playing();
      }
      sample_trigger[0][0] = 0;
    }

    if (sample_trigger[0][1] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform2.sample_play();
        check_playing();
      }
      sample_trigger[0][1] = 0;
    }
    if (sample_trigger[0][2] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform3.sample_play();
        check_playing();
      }
      sample_trigger[0][2] = 0;
    }
    if (sample_trigger[0][3] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform4.sample_play();
        check_playing();
      }
      sample_trigger[0][3] = 0;
    }
    if (sample_trigger[0][4] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform5.sample_play();
        check_playing();
      }
      sample_trigger[0][4] = 0;
    }
    if (sample_trigger[0][5] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform6.sample_play();
        check_playing();
      }
      sample_trigger[0][5] = 0;
    }
    if (sample_trigger[0][6] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform7.sample_play();
        check_playing();
      }
      sample_trigger[0][6] = 0;
    }
    if (sample_trigger[0][7] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform8.sample_play();
        check_playing();
      }
      sample_trigger[0][7] = 0;
    }
    if (sample_trigger[0][8] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform9.sample_play();
        check_playing();
      }
      sample_trigger[0][8] = 0;
    }


    if (sample_trigger[1][0] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform10.sample_play();
        check_playing();
      }
      sample_trigger[1][0] = 0;
    }
    if (sample_trigger[1][1] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform11.sample_play();
        check_playing();
      }
      sample_trigger[1][1] = 0;
    }
    if (sample_trigger[1][2] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform12.sample_play();
        check_playing();
      }
      sample_trigger[1][2] = 0;
    }
    if (sample_trigger[1][3] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform13.sample_play();
        check_playing();
      }
      sample_trigger[1][3] = 0;
    }
    if (sample_trigger[1][4] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform14.sample_play();
        check_playing();
      }
      sample_trigger[1][4] = 0;
    }
    if (sample_trigger[1][5] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform15.sample_play();
        check_playing();
      }
      sample_trigger[1][5] = 0;
    }
    if (sample_trigger[1][6] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform16.sample_play();
        check_playing();
      }
      sample_trigger[1][6] = 0;
    }
    if (sample_trigger[1][7] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform17.sample_play();
        check_playing();
      }
      sample_trigger[1][7] = 0;
    }
    if (sample_trigger[1][8] == 1) {
      if (num_playing < MAX_PLAYING) {
        waveform18.sample_play();
        check_playing();
      }
      sample_trigger[1][8] = 0;
    }
  }





  ////////////////////////////////////////////////// SEQ

  if (cm - prev[4] > seq_rate && major_mode == 1) {
    prev[4] = cm;


    if (seq_mode == PRE_PLAYBACK_MODE && seq_exit == 0)
    {
      //Serial.rint("hey ");
      //Serial.rintln(seq_count);
      if (midionce == 0) {

        if (player_sel == 0) {
          MIDI.sendControlChange(2, READY, 1 );
          MIDI.sendControlChange(2, ARROW, 2);
        }
        if (player_sel == 1) {
          MIDI.sendControlChange(2, ARROW, 1);
          MIDI.sendControlChange(2, READY, 2);
        }

        midionce = 1;
      }

      if ((seq_count) % 4 == 0) {
        drum1.noteOn();
        // waveform17.sample_play();
      }

      if (seq_count == 16) {
        if (player_sel == 0) {
          MIDI.sendControlChange(2, LISTEN, 1 );
          MIDI.sendControlChange(2, ARROW, 2);
        }
        if (player_sel == 1) {
          MIDI.sendControlChange(2, ARROW, 1);
          MIDI.sendControlChange(2, LISTEN, 2);
        }
      }

      seq_count++;
      if (seq_count > (SEQ_LEN - 1)) {
        seq_count = 0;
        seq_mode = PLAYBACK_MODE;
        ////print1();
        midionce = 0;
        //MIDI.sendControlChange(2, seq_mode, 1);
      }

    }


    if (seq_mode == PLAYBACK_MODE && seq_exit == 0)
    {
      //Serial.rintln(seq_count);

      if (midionce == 0) {

        if (player_num == 0) {
          MIDI.sendControlChange(2, LISTEN, 1);
        }

        if (player_num > 0) {
          if (player_sel == 0) {
            MIDI.sendControlChange(2, LISTEN, 1 );
            MIDI.sendControlChange(2, ARROW, 2);
          }
          if (player_sel == 1) {
            MIDI.sendControlChange(2, ARROW, 1);
            MIDI.sendControlChange(2, LISTEN, 2);
          }
        }
        midionce = 1;
      }

      for (int se = 0; se < BUTT_NUM ; se++)
      {
        if (sequences[difficulty][lvl][se][seq_count] == 1) {
          sample_trigger[player_sel][se] = 1;
          button_led_output[player_sel][se] = 255;
          button_led_state[player_sel][se] = 1;
        }
      }

      if ((seq_count) % 4 == 0) {
        if (player_sel == 0) {
          waveform19.sample_play();
        }
        if (player_sel == 1) {
          waveform20.sample_play();
        }
      }

      seq_count++;
      if (seq_count > SEQ_LEN - 1) {
        seq_count = 0;
        seq_mode = WAIT_AFTER_PLAY_MODE;
        midionce = 0;
        seq_exit = 1;
        //print1();
      }
    }

    if (seq_mode == WAIT_AFTER_PLAY_MODE && seq_exit == 0)
    {

      if (midionce == 0) {

        if (player_num == 0) {
          MIDI.sendControlChange(2, READY, 1);
        }

        if (player_num > 0) {
          if (player_sel == 0) {
            MIDI.sendControlChange(2, READY, 1 );
            MIDI.sendControlChange(2, ARROW, 2);
          }
          if (player_sel == 1) {
            MIDI.sendControlChange(2, ARROW, 1);
            MIDI.sendControlChange(2, READY, 2);
          }
        }
        midionce = 1;
      }

      if ((seq_count) % 4 == 0) {
        drum1.noteOn();

      }


      byte sc = 16;
      for (int m = 4; m > 0; m--) {
        if (seq_count == sc) {
          if (player_sel == 0) {
            MIDI.sendControlChange(0, m, 1);
          }
          if (player_sel == 1) {
            MIDI.sendControlChange(0, m, 2);

          }
        }
        sc += 4;
      }


      seq_count++;
      if (seq_count > SEQ_LEN - 1) {
        seq_count = 0;
        seq_mode = LISTEN_MODE;
        seq_exit = 1;
        midionce = 0;
        //print1();

        for (int br = 0; br < BUTT_NUM; br++) {
          score_lock[player_sel][br] = 0;
        }
      }

    }

    if (seq_mode == LISTEN_MODE && seq_exit == 0)
    {
      if (midionce == 0) {

        if (player_sel == 0) {
          MIDI.sendControlChange(2, GO, 1 );
          MIDI.sendControlChange(2, ARROW, 2);
        }
        if (player_sel == 1) {
          MIDI.sendControlChange(2, ARROW, 1);
          MIDI.sendControlChange(2, GO, 2);
        }

        midionce = 1;
      }

      byte sc = 8;
      for (int m = 6; m > 0; m--) {
        if (seq_count == sc) {
          if (player_sel == 0) {
            MIDI.sendControlChange(0, m, 1);
          }
          if (player_sel == 1) {
            MIDI.sendControlChange(0, m, 2);
          }
        }
        sc += 4;
      }

      if ((seq_count) % 4 == 0) {

        if (player_sel == 0) {
          waveform19.sample_play();
        }
        if (player_sel == 1) {
          waveform20.sample_play();
        }

      }

      seq_count++;

      byte nsc = seq_count + 1 % SEQ_LEN;
      byte psc = seq_count - 1;
      if (psc < 0) {
        psc += SEQ_LEN;
      }
      for (int br = 0; br < BUTT_NUM; br++) {

        if (sequences[difficulty][lvl][br][nsc] == 1) {
          score_lock[player_sel][br] = 0;
        }
      }

      if (seq_count > SEQ_LEN - 1) {
        if (player_num > 0) {
          if (player_sel == 0) {
            seq_count = 0;
            seq_mode = PRE_PLAYBACK_MODE;
            player_sel = 1;
            midionce = 0;
            seq_exit = 1;

          }
          if (player_sel == 1 && seq_exit == 0) {
            seq_count = 0;
            seq_mode = DISPLAY_SCORE;
            player_sel = 0;
            midionce = 0;
            seq_exit = 1;

          }
        }

        if (player_num == 0) {
          player_sel = 0;
          seq_count = 0;
          seq_mode = DISPLAY_SCORE;
          midionce = 0;
          seq_exit = 1;
          //print1();

        }
      }


    }

    if (seq_mode == DISPLAY_SCORE && seq_exit == 0)
    {

      if (midionce == 0) {
        lvl++;

        midionce = 1;
        if (player_num == 0) {
          MIDI.sendControlChange(2, ARROW, 2);

          if (score[0] > 6) {
            MIDI.sendControlChange(2, WOW, 1);
          }
          if (score[0] > 3 &&  score[0] < 6) {
            MIDI.sendControlChange(2, GREAT, 1);
          }
          if (score[0] <= 3) {
            MIDI.sendControlChange(2, COOL, 1);
          }
          full_score[0] += score[0];
          score[0] = 0;
        }

        if (player_num > 0) {
          for (byte ps = 0; ps < 2; ps++) {
            if (score[0] > 6) {
              MIDI.sendControlChange(2, WOW, ps + 1);
            }
            if (score[ps] > 3 &&  score[ps] < 6) {
              MIDI.sendControlChange(2, GREAT, ps + 1);
            }
            if (score[ps] <= 3) {
              MIDI.sendControlChange(2, COOL, ps + 1);
            }
            full_score[ps] += score[ps];
            score[ps] = 0;
          }
        }
      }



      if ( lvl < 6) {


        if ((seq_count) % 8 == 0) {
          drum1.noteOn();
          // waveform17.sample_play();
        }
        if (player_num == 0) {
          MIDI.sendControlChange(2, ARROW, 2);

          if (seq_count == 16) {
            MIDI.sendControlChange(2, SCORE, 1);
          }

          if (seq_count == 24) {
            MIDI.sendControlChange(1, full_score[0], 1);
          }

          if (seq_count == 32) {
            MIDI.sendControlChange(2, LEVEL, 1);
          }

          if (seq_count == 40) {
            MIDI.sendControlChange(0, lvl + 1, 1);
          }


          if (seq_count == 48) {
            MIDI.sendControlChange(2, READY, 1);
          }
          full_score[0] += score[0];
          score[0] = 0;
        }

        if (player_num > 0) {
          for (byte ps = 0; ps < 2; ps++) {

            if (seq_count == 16) {
              MIDI.sendControlChange(2, SCORE, 1);
              MIDI.sendControlChange(2, SCORE, 2);

            }

            if (seq_count == 24) {
              MIDI.sendControlChange(1, full_score[0], 1);
              MIDI.sendControlChange(1, full_score[1], 2);

            }

            if (seq_count == 40) {
              MIDI.sendControlChange(2, LEVEL, 1);
              MIDI.sendControlChange(2, LEVEL, 2);

            }

            if (seq_count == 48) {
              MIDI.sendControlChange(1, lvl + 1, 1);
              MIDI.sendControlChange(1, lvl + 1, 2);

            }


            if (seq_count == 56) {
              MIDI.sendControlChange(2, READY, 1);
              MIDI.sendControlChange(2, ARROW, 2);

            }
            full_score[ps] += score[ps];
            score[ps] = 0;

          }
        }

        seq_count++;
        if (seq_count > (SEQ_LEN - 1) * 2) {
          seq_count = 0;
          seq_mode = PLAYBACK_MODE;
          //print1();
          midionce = 0;
          //player_sel = 0;
          //MIDI.sendControlChange(2, seq_mode, 1);


        }
      }
      if (lvl >= 6) {

        if (seq_count < 48) {
          if ((seq_count) % 1 == 0) {
            sample_trigger[0][random(8)] = 1;
          }
          if ((seq_count) % 2 == 0) {
            sample_trigger[1][random(8)] = 1;
          }
        }

        if (player_num == 0) {
          MIDI.sendControlChange(2, ARROW, 2);

          if (seq_count == 16) {
            MIDI.sendControlChange(2, FINAL, 1);
          }

          if (seq_count == 32) {
            MIDI.sendControlChange(2, SCORE, 1);
          }

          if (seq_count == 48) {
            MIDI.sendControlChange(1, full_score[0], 1);
          }


        }

        if (player_num > 0) {
          for (byte ps = 0; ps < 2; ps++) {

            if (seq_count == 16) {
              MIDI.sendControlChange(2, FINAL, 1);
              MIDI.sendControlChange(2, FINAL, 2);
            }

            if (seq_count == 32) {
              MIDI.sendControlChange(2, SCORE, 1);
              MIDI.sendControlChange(2, SCORE, 2);
            }

            if (seq_count == 48) {
              MIDI.sendControlChange(1, full_score[0], 1);
              MIDI.sendControlChange(1, full_score[1], 2);
            }
          }
        }

        seq_count++;
        if (seq_count > (SEQ_LEN - 1) * 3) {
          lvl = 0;
          player_num = 0;
          player_sel = 0;
          seq_count = 0;
          seq_mode = BUTTON_WAIT;
          //print1();
          midionce = 0;
          major_mode = 0;
          difficulty = 0;
          seq_rate = easy_speed;
          //MIDI.sendControlChange(2, seq_mode, 1);

        }

      }






    }


    if (seq_mode == STOP_MODE && seq_exit == 0)
    {
      timeout = 0;
      if (any_button_pressed == 1 && 1 == 1) { //////////////////////////////////////////////////////////!!!!!!!!!!!!!!
        //Serial.rintln("!");
        any_button_pressed = 0;
        seq_mode = GET_READY;
        seq_count = 0;
        seq_exit = 0;
        midionce = 0;

        // MIDI.sendControlChange(2, seq_mode, 1);
      }

    }


    if (seq_mode == BUTTON_WAIT && seq_exit == 0)
    {

      if (ready_count < 8 ) {
        MIDI.sendControlChange(2, OKAY, 1);
        MIDI.sendControlChange(2, OKAY, 2);

      }
      if (ready_count >= 8 ) {


        if (player_in[0] == 1) {

          MIDI.sendControlChange(2, ONE_PLAY, 1);

          if ((ready_count) % 8 == 0) {
            MIDI.sendControlChange(2, PRESS, 2);
          }
          if ((ready_count) % 16 == 0) {
            MIDI.sendControlChange(2, BUTTON, 2);
          }
        }

        if (player_in[1] == 1) {
          MIDI.sendControlChange(2, TWO_PLAY, 2);
          MIDI.sendControlChange(2, TWO_PLAY, 1);
        }

        if (player_in[0] == 0) {
          if ((ready_count) % 8 == 0) {
            MIDI.sendControlChange(2, PRESS, 1);
            MIDI.sendControlChange(2, PRESS, 2);
          }
          if ((ready_count) % 16 == 0) {
            MIDI.sendControlChange(2, BUTTON, 1);
            MIDI.sendControlChange(2, BUTTON, 2);
          }

        }
      }

      ready_count++;
      /*
        if (ready_count > 64) {
        major_mode = 0;
        MIDI.sendControlChange(3, 0, 1);
        MIDI.sendControlChange(3, 0, 2);

        }
      */

      if (any_button_pressed == 1 && wait_button_once[0] == 0) {
        player_in[0] = 1;
        countdown = 32;
        ready_count = 0;
        player_num = 0;
        wait_button_once[0] = 1;

      }

      if (any_button_pressed == 2 && wait_button_once[1] == 0) {
        player_num = 1;
        player_in[1] = 1;
        MIDI.sendControlChange(2, TWO_PLAY, 1);
        MIDI.sendControlChange(2, TWO_PLAY, 2);
        countdown = 8;
        ready_count = 0;
        wait_button_once[1] = 1;

      }

      if (countdown > 0) {

        if ((ready_count) % 4 == 0) {
          drum1.frequency(drum_freq[1]);
          drum1.noteOn();
          // waveform17.sample_play();
        }
        if ((ready_count) % 8 == 0) {
          drum1.frequency(drum_freq[2]);
          drum1.noteOn();
          // waveform17.sample_play();
        }


      }


      if (countdown > 0 && ready_count > countdown) {
        if (player_num == 0) {
          MIDI.sendControlChange(2, ARROW, 2);
        }

        seq_count = 0;
        countdown = 0;
        seq_mode = PRE_PLAYBACK_MODE;
        seq_exit = 1;
        midionce = 0;
        any_button_pressed = 0;
        ready_count = 0;
        player_sel = 0;
        wait_button_once[0] = 0;
        wait_button_once[1] = 0;
        player_in[0] = 0;
        player_in[1] = 0;
        drum1.frequency(drum_freq[0]);
        //print1();

      }
    }
    /*
        if (seq_mode == GET_READY && seq_exit == 0) {

          if ((seq_count) % 4 == 0 && seq_count > 0 ) {
            MIDI.sendControlChange(2, READY, 1);
            drum1.noteOn();

            // waveform17.sample_play();

          }

          seq_count++;

          if (seq_count > (SEQ_LEN - 1) / 2) {
            seq_count = 0;
            seq_mode = PLAYBACK_MODE;
            seq_exit = 1;
            midionce = 0;
            ready_count = 0;
            //print1();
            //MIDI.sendControlChange(2, seq_mode, 1);
          }


        }
    */
    any_button_pressed = 0;
    seq_exit = 0;
  }



  if (cm - prev[0] > 100 && 1 == 1) {
    prev[0] = cm;

    Serial.print("p ");
    Serial.print(AudioProcessorUsageMax());  //go over 90% and you'll start to glitch out
    Serial.print("   m ");
    Serial.println(AudioMemoryUsageMax()); //if this number is bigger than what you entered in  AudioMemory(??) in setup make it bigger
    /*
      Serial.print("player_sel ");
      Serial.println(player_sel);
      Serial.print("player_num ");
      Serial.println(player_num);
      Serial.println();
    */
    /*
      for (int h = 0; h < 9; h++) {
      Serial.print(button_reading[0][h]);
      Serial.print(" ");
      }
      Serial.println( );
      for (int h = 0; h < 9; h++) {
      Serial.print(button_reading[1][h]);
      Serial.print(" ");
      }
      Serial.println( );
      for (int h = 0; h < 3; h++) {
      Serial.print(ctrl_reading[h]);
      Serial.print(" ");
      }
      Serial.println( );
    */
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();

    Serial.println();
  }


}


// you could do a polyphic type thing where the frist note is cut but that sounds unecessary
void check_playing() {
  // num_playing = waveform1.sample_status() + waveform2.sample_status() + waveform3.sample_status() + waveform4.sample_status();

}

void print1() {
  Serial.print("seq_mode ");


  if (seq_mode == 1) {
    Serial.print("PLAYBACK_MODE");
  }
  if (seq_mode == 2) {
    Serial.print("WAIT_AFTER_PLAY_MODE");
  }
  if (seq_mode == 3) {
    Serial.print("LISTEN_MODE");
  }
  if (seq_mode == 4) {
    Serial.print("DISPLAY_SCORE");
  }
  if (seq_mode == 5) {
    Serial.print("STOP_MODE");
  }
  if (seq_mode == 6) {
    Serial.print("GET_READY");
  }
  if (seq_mode == 7) {
    Serial.print("BUTTON_WAIT");
  }
  if (seq_mode == 8) {
    Serial.print("PRE_PLAYBACK_MODE");
  }
  Serial.print("  scores ");
  Serial.print(score[0]);
  Serial.print(" ");
  Serial.println(score[1]);
  Serial.println();
}



