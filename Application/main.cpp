#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <thread>
#include <string>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include <condition_variable>
#include <map>
Config config;
using namespace std;
using std::cout;
using std::endl;
using std::reverse;
using std::string;
#define RFID_PATH config.DEV_TTY
#define POWER_METER_PATH config.DEV_TTY2
#define LCD_PATH config.qled_path


void LCD_date(int state)
{
    uint8_t cmd0_data2[8], cmd0_data3[8];
    uint8_t cmd1_data2[8], cmd1_data3[8];
    uint8_t cmd2_data2[8], cmd2_data3[8];
    uint8_t cmd3_data2[8], cmd3_data3[8];
    uint8_t cmd4_data2[8], cmd4_data3[8];
    uint8_t cmd5_data2[8], cmd5_data3[8];
    uint8_t cmd0_data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cmd1_data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cmd2_data1[8] = {0, 0, 0, 1, 0, 0, 0, 0};
    uint8_t cmd3_data1[8] = {0, 0, 1, 1, 0, 0, 0, 0};
    uint8_t cmd4_data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cmd5_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    speed_t speed = B9600;
    int vtime = 1;
    size_t tx_len = 6;
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    // Get year, month, day
    int year = (localTime->tm_year + 1900) % 100;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    // Get hours, minutes, seconds
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;
    // Store the tens and ones digits of hours, minutes, and seconds separately
    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = minute / 10;
    int minute2 = minute % 10;
    int second1 = second / 10;
    int second2 = second % 10;
    // Store the tens and ones digits of the year, month, and day separately
    int year1 = year / 10;
    int year2 = year % 10;
    int month1 = month / 10;
    int month2 = month % 10;
    int day1 = day / 10;
    int day2 = day % 10;
    value_to_bin(day2, cmd5_data2);
    value_to_bin(day1, cmd4_data2);
    value_to_bin(month2, cmd3_data2);
    value_to_bin(month1, cmd2_data2);
    value_to_bin(year2, cmd1_data2);
    value_to_bin(year1, cmd0_data2);
    value_to_bin(-1, cmd5_data3);
    value_to_bin(-1, cmd4_data3);
    value_to_bin(-1, cmd3_data3);
    value_to_bin(-1, cmd2_data3);
    value_to_bin(-1, cmd1_data3);
    value_to_bin(-1, cmd0_data3);
    if (state == 1)
    {
        cmd2_data1[3] = 1;
    }
    else
    {
        cmd2_data1[3] = 0;
    }
    uint8_t *cmd0 = set_led_bytes(0, cmd0_data1, cmd0_data2, cmd0_data3);
    uint8_t *cmd1 = set_led_bytes(1, cmd1_data1, cmd1_data2, cmd1_data3);
    uint8_t *cmd2 = set_led_bytes(2, cmd2_data1, cmd2_data2, cmd2_data3);
    uint8_t *cmd3 = set_led_bytes(3, cmd3_data1, cmd3_data2, cmd3_data3);
    uint8_t *cmd4 = set_led_bytes(4, cmd4_data1, cmd4_data2, cmd4_data3);
    uint8_t *cmd5 = set_led_bytes(5, cmd5_data1, cmd5_data2, cmd5_data3);
    uart_write(QLED_PATH, speed, vtime, cmd0, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd1, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd2, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd3, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd4, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd5, tx_len);
}
void LCD_time(int state)
{
    uint8_t cmd0_data2[8], cmd0_data3[8];
    uint8_t cmd1_data2[8], cmd1_data3[8];
    uint8_t cmd2_data2[8], cmd2_data3[8];
    uint8_t cmd3_data2[8], cmd3_data3[8];
    uint8_t cmd4_data2[8], cmd4_data3[8];
    uint8_t cmd5_data2[8], cmd5_data3[8];
    uint8_t cmd0_data1[8] = {0, 0, 0, 1, 0, 0, 0, 0};
    uint8_t cmd1_data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t cmd2_data1[8] = {0, 0, 1, 1, 0, 0, 0, 0};
    uint8_t cmd3_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd4_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd5_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    speed_t speed = B9600;
    int vtime = 1;
    size_t tx_len = 6;
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    // 取年、月、日
    int year = (localTime->tm_year + 1900) % 100;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    // 取時、分、秒
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;
    // 分別存儲時、分、秒的十位和個位數
    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = minute / 10;
    int minute2 = minute % 10;
    int second1 = second / 10;
    int second2 = second % 10;
    // 分別存儲年、月、日的十位和個位數
    int year1 = year / 10;
    int year2 = year % 10;
    int month1 = month / 10;
    int month2 = month % 10;
    int day1 = day / 10;
    int day2 = day % 10;
    value_to_bin(second2, cmd5_data2);
    value_to_bin(second1, cmd4_data2);
    value_to_bin(minute2, cmd3_data2);
    value_to_bin(minute1, cmd2_data2);
    value_to_bin(hour2, cmd1_data2);
    value_to_bin(hour1, cmd0_data2);
    value_to_bin(-1, cmd5_data3);
    value_to_bin(-1, cmd4_data3);
    value_to_bin(-1, cmd3_data3);
    value_to_bin(-1, cmd2_data3);
    value_to_bin(-1, cmd1_data3);
    value_to_bin(-1, cmd0_data3);
    if (state == 1)
    {
        cmd2_data1[3] = 1;
    }
    else
    {
        cmd2_data1[3] = 0;
    }
    uint8_t *cmd0 = set_led_bytes(0, cmd0_data1, cmd0_data2, cmd0_data3);
    uint8_t *cmd1 = set_led_bytes(1, cmd1_data1, cmd1_data2, cmd1_data3);
    uint8_t *cmd2 = set_led_bytes(2, cmd2_data1, cmd2_data2, cmd2_data3);
    uint8_t *cmd3 = set_led_bytes(3, cmd3_data1, cmd3_data2, cmd3_data3);
    uint8_t *cmd4 = set_led_bytes(4, cmd4_data1, cmd4_data2, cmd4_data3);
    uint8_t *cmd5 = set_led_bytes(5, cmd5_data1, cmd5_data2, cmd5_data3);
    uart_write(QLED_PATH, speed, vtime, cmd0, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd1, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd2, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd3, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd4, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd5, tx_len);
}
void LCD_init(int mode)
{
    uint8_t cmd0_data1[8], cmd0_data2[8], cmd0_data3[8];
    uint8_t cmd1_data1[8], cmd1_data2[8], cmd1_data3[8];
    uint8_t cmd2_data1[8], cmd2_data2[8], cmd2_data3[8];
    uint8_t cmd3_data1[8], cmd3_data2[8], cmd3_data3[8];
    uint8_t cmd4_data1[8], cmd4_data2[8], cmd4_data3[8];
    uint8_t cmd5_data1[8], cmd5_data2[8], cmd5_data3[8];
    speed_t speed = B9600;
    int vtime = 1;
    size_t tx_len = 6;
    value_to_bin(mode, cmd5_data1);
    value_to_bin(mode, cmd5_data2);
    value_to_bin(mode, cmd5_data3);
    value_to_bin(mode, cmd4_data1);
    value_to_bin(mode, cmd4_data2);
    value_to_bin(mode, cmd4_data3);
    value_to_bin(mode, cmd3_data1);
    value_to_bin(mode, cmd3_data2);
    value_to_bin(mode, cmd3_data3);
    value_to_bin(mode, cmd2_data1);
    value_to_bin(mode, cmd2_data2);
    value_to_bin(mode, cmd2_data3);
    value_to_bin(mode, cmd1_data1);
    value_to_bin(mode, cmd1_data2);
    value_to_bin(mode, cmd1_data3);
    value_to_bin(mode, cmd0_data1);
    value_to_bin(mode, cmd0_data2);
    value_to_bin(mode, cmd0_data3);
    uint8_t *cmd0 = set_led_bytes(0, cmd0_data1, cmd0_data2, cmd0_data3);
    uint8_t *cmd1 = set_led_bytes(1, cmd1_data1, cmd1_data2, cmd1_data3);
    uint8_t *cmd2 = set_led_bytes(2, cmd2_data1, cmd2_data2, cmd2_data3);
    uint8_t *cmd3 = set_led_bytes(3, cmd3_data1, cmd3_data2, cmd3_data3);
    uint8_t *cmd4 = set_led_bytes(4, cmd4_data1, cmd4_data2, cmd4_data3);
    uint8_t *cmd5 = set_led_bytes(5, cmd5_data1, cmd5_data2, cmd5_data3);
    uart_write(QLED_PATH, speed, vtime, cmd0, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd1, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd2, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd3, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd4, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd5, tx_len);
}
void LCD_alarm(int mode, int errcodes)
{
    uint8_t cmd0_data1[8], cmd0_data2[8], cmd0_data3[8];
    uint8_t cmd1_data1[8], cmd1_data2[8], cmd1_data3[8];
    uint8_t cmd2_data1[8], cmd2_data2[8], cmd2_data3[8];
    uint8_t cmd3_data1[8], cmd3_data2[8], cmd3_data3[8];
    uint8_t cmd4_data1[8], cmd4_data2[8], cmd4_data3[8];
    uint8_t cmd5_data1[8], cmd5_data2[8], cmd5_data3[8];
    speed_t speed = B9600;
    int vtime = 1;
    size_t tx_len = 6;

    value_to_bin(mode, cmd5_data1);
    value_to_bin(mode, cmd5_data2);
    value_to_bin(mode, cmd5_data3);
    value_to_bin(mode, cmd4_data1);
    value_to_bin(mode, cmd4_data2);
    value_to_bin(mode, cmd4_data3);
    value_to_bin(mode, cmd3_data1);
    value_to_bin(mode, cmd3_data2);
    value_to_bin(mode, cmd3_data3);
    value_to_bin(mode, cmd2_data1);
    value_to_bin(mode, cmd2_data2);
    value_to_bin(mode, cmd2_data3);
    value_to_bin(mode, cmd1_data1);
    value_to_bin(mode, cmd1_data2);
    value_to_bin(mode, cmd1_data3);
    value_to_bin(mode, cmd0_data1);
    value_to_bin(mode, cmd0_data2);
    value_to_bin(mode, cmd0_data3);
    cmd0_data1[2] = 1;
    cmd0_data3[0] = 1;
    cmd0_data3[3] = 1;
    cmd0_data3[4] = 1;
    cmd0_data3[5] = 1;
    cmd0_data3[6] = 1;
    cmd1_data3[4] = 1;
    cmd1_data3[6] = 1;
    cmd2_data3[4] = 1;
    cmd2_data3[6] = 1;

    int errcode = errcodes / 100;
    int errcode1 = (errcodes / 10) % 10;
    int errcode2 = errcodes % 10;
    value_to_bin(errcode2, cmd5_data3);
    value_to_bin(errcode1, cmd4_data3);
    value_to_bin(errcode, cmd3_data3);

    uint8_t *cmd0 = set_led_bytes(0, cmd0_data1, cmd0_data2, cmd0_data3);
    uint8_t *cmd1 = set_led_bytes(1, cmd1_data1, cmd1_data2, cmd1_data3);
    uint8_t *cmd2 = set_led_bytes(2, cmd2_data1, cmd2_data2, cmd2_data3);
    uint8_t *cmd3 = set_led_bytes(3, cmd3_data1, cmd3_data2, cmd3_data3);
    uint8_t *cmd4 = set_led_bytes(4, cmd4_data1, cmd4_data2, cmd4_data3);
    uint8_t *cmd5 = set_led_bytes(5, cmd5_data1, cmd5_data2, cmd5_data3);

    uart_write(QLED_PATH, speed, vtime, cmd0, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd1, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd2, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd3, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd4, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd5, tx_len);
}
void ChargingTime(int seconds, int energy, bool *state, int checkout, int alarm)
{
    uint8_t cmd0_data2[8], cmd0_data3[8];
    uint8_t cmd1_data2[8], cmd1_data3[8];
    uint8_t cmd2_data2[8], cmd2_data3[8];
    uint8_t cmd3_data2[8], cmd3_data3[8];
    uint8_t cmd4_data2[8], cmd4_data3[8];
    uint8_t cmd5_data2[8], cmd5_data3[8];
    uint8_t cmd0_data1[8] = {0, 0, 0, 1, 0, 0, 0, 0};
    uint8_t cmd1_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd2_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd3_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd4_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    uint8_t cmd5_data1[8] = {0, 0, 1, 0, 0, 0, 0, 0};
    speed_t speed = B9600;
    int vtime = 1;
    size_t tx_len = 6;
    int icon_state = 0;
    int hour = seconds / 3600;
    int minute = (seconds % 3600) / 60;
    int second = seconds % 60;
    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = minute / 10;
    int minute2 = minute % 10;
    int second1 = second / 10;
    int second2 = second % 10;

    int energy0, energy1, energy2, energy3, energy4, energy5;
    if (energy > 999999)
    {
        energy = 999999;
    }
    energy0 = energy / 100000;
    energy1 = (energy / 10000) % 10;
    energy2 = (energy / 1000) % 10;
    energy3 = (energy / 100) % 10;
    energy4 = (energy / 10) % 10;
    energy5 = energy % 10;
    if (count_digits(energy) <= 4)
    {
        energy0 = -1;
        energy1 = -1;
    }
    else if (count_digits(energy) == 5)
    {
        energy0 = -1;
    }
    icon_state = seconds / ICON_FLASHING_TIME;
    if (icon_state == 0)
    {
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd0_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd0_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 1)
    {
        cmd0_data1[0] = 1;
        if (checkout == 0 & alarm == 0)
        {
            if (*state == false)
            {
                cmd1_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd1_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 2)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd2_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd2_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 3)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd3_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd3_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 4)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd4_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd4_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 5)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        cmd4_data1[0] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd5_data1[0] = 1;
                *state = true;
            }
            else
            {
                cmd5_data1[0] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 6)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        cmd4_data1[0] = 1;
        cmd5_data1[0] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd5_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd5_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 7)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        cmd4_data1[0] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd4_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd4_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 8)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        cmd4_data1[0] = 1;
        cmd4_data1[1] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd3_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd3_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 9)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd3_data1[0] = 1;
        cmd3_data1[1] = 1;
        cmd4_data1[0] = 1;
        cmd4_data1[1] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd2_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd2_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 10)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd2_data1[0] = 1;
        cmd2_data1[1] = 1;
        cmd3_data1[0] = 1;
        cmd3_data1[1] = 1;
        cmd4_data1[0] = 1;
        cmd4_data1[1] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd1_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd1_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state == 11)
    {
        cmd0_data1[0] = 1;
        cmd1_data1[0] = 1;
        cmd1_data1[1] = 1;
        cmd2_data1[0] = 1;
        cmd2_data1[1] = 1;
        cmd3_data1[0] = 1;
        cmd3_data1[1] = 1;
        cmd4_data1[0] = 1;
        cmd4_data1[1] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
        if (checkout == 0 && alarm == 0)
        {
            if (*state == false)
            {
                cmd0_data1[1] = 1;
                *state = true;
            }
            else
            {
                cmd0_data1[1] = 0;
                *state = false;
            }
        }
    }
    else if (icon_state >= 12)
    {
        cmd0_data1[0] = 1;
        cmd0_data1[1] = 1;
        cmd1_data1[0] = 1;
        cmd1_data1[1] = 1;
        cmd2_data1[0] = 1;
        cmd2_data1[1] = 1;
        cmd3_data1[0] = 1;
        cmd3_data1[1] = 1;
        cmd4_data1[0] = 1;
        cmd4_data1[1] = 1;
        cmd5_data1[0] = 1;
        cmd5_data1[1] = 1;
    }

    value_to_bin(second2, cmd5_data2);
    value_to_bin(energy5, cmd5_data3);
    value_to_bin(second1, cmd4_data2);
    value_to_bin(energy4, cmd4_data3);
    value_to_bin(minute2, cmd3_data2);
    value_to_bin(energy3, cmd3_data3);
    value_to_bin(minute1, cmd2_data2);
    value_to_bin(energy2, cmd2_data3);

    value_to_bin(hour2, cmd1_data2);
    value_to_bin(energy1, cmd1_data3);
    value_to_bin(hour1, cmd0_data2);
    value_to_bin(energy0, cmd0_data3);
    if (alarm == 1)
    {
        cmd0_data1[2] = 1;
    }
    else
    {
        cmd0_data1[2] = 0;
    }
    if (checkout == 1)
    {
        cmd2_data3[7] = 0;
        cmd1_data1[2] = 0;
        cmd1_data1[3] = 1;
        cmd2_data1[3] = 1;
    }
    else
    {
        cmd2_data3[7] = 1;
        cmd1_data1[2] = 1;
        cmd1_data1[3] = 0;
        cmd2_data1[3] = 0;
    }

    uint8_t *cmd0 = set_led_bytes(0, cmd0_data1, cmd0_data2, cmd0_data3);
    uint8_t *cmd1 = set_led_bytes(1, cmd1_data1, cmd1_data2, cmd1_data3);
    uint8_t *cmd2 = set_led_bytes(2, cmd2_data1, cmd2_data2, cmd2_data3);
    uint8_t *cmd3 = set_led_bytes(3, cmd3_data1, cmd3_data2, cmd3_data3);
    uint8_t *cmd4 = set_led_bytes(4, cmd4_data1, cmd4_data2, cmd4_data3);
    uint8_t *cmd5 = set_led_bytes(5, cmd5_data1, cmd5_data2, cmd5_data3);
    uart_write(QLED_PATH, speed, vtime, cmd0, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd1, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd2, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd3, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd4, tx_len);
    uart_write(QLED_PATH, speed, vtime, cmd5, tx_len);
}