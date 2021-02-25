#pragma once
#include <Arduino.h>

// описание класса
class Seven_segment {   // класс Seven_segment
public:
	Seven_segment(byte pin11, byte pin12, byte pin14);
	void attach(byte pin11, byte pin12, byte pin14);
	void write(byte num);
	void write(long int num);
	void write(char num);
	void write(int num);
	void write(String num);
	byte get();
	void setShift(byte shift);
	void addDot();
	void removeDot();
	void clear();
	void fill();
	void send(byte num);
private:
	byte _bs[10] = {
		0b01111110,
		0b00011000,
		0b01101101,
		0b00111101,
		0b00011011,
		0b00110111,
		0b01110111,
		0b00011100,
		0b01111111,
		0b00111111
	};
	byte _pin11;
	byte _pin12;
	byte _pin14;
	byte _num;
	byte _shift = 0;
};

// реализация методов
Seven_segment::Seven_segment(byte pin11, byte pin12, byte pin14) { // конструктор
	_pin11 = pin11;
	_pin12 = pin12;
	_pin14 = pin14;
	pinMode(_pin11, OUTPUT);
	pinMode(_pin12, OUTPUT);
	pinMode(_pin14, OUTPUT);
}

void Seven_segment::attach(byte pin11, byte pin12, byte pin14) {
	_pin11 = pin11;
	_pin12 = pin12;
	_pin14 = pin14;
	pinMode(_pin11, OUTPUT);
	pinMode(_pin12, OUTPUT);
	pinMode(_pin14, OUTPUT);
}

void Seven_segment::write(byte num) {
	pinMode(_pin11, OUTPUT);
	pinMode(_pin12, OUTPUT);
	pinMode(_pin14, OUTPUT);
	_num = _bs[num % 10];
	digitalWrite(_pin12, LOW);
	shiftOut(_pin14, _pin11,LSBFIRST, _bs[num % 10] + _shift);
	digitalWrite(_pin12, HIGH);
}

void Seven_segment::send(byte num) {
	pinMode(_pin11, OUTPUT);
	pinMode(_pin12, OUTPUT);
	pinMode(_pin14, OUTPUT);
	_num = num;
	digitalWrite(_pin12, LOW);
	shiftOut(_pin14, _pin11,LSBFIRST, num);
	digitalWrite(_pin12, HIGH);
}

void Seven_segment::clear() {
	send(0b00000000);
	_num = 0b00000000;
	removeDot();
}

void Seven_segment::fill() {
	_num = 0b11111111;
	send(0b11111111);
}

void Seven_segment::write(char num) {
	write(String(num));
}

void Seven_segment::write(long int num) {
	write((byte)num);
}

void Seven_segment::write(int num) {
	write((byte)num);
}

void Seven_segment::write(String num) {
	write(num.toInt());
}
byte Seven_segment::get() {
	return _num;
}
void Seven_segment::addDot() {
	_shift = 128;
	send(_num + _shift);
}
void Seven_segment::removeDot() {
	_shift = 0;
	send(_num + _shift);
}
void Seven_segment::setShift(byte shift) {
	_shift = shift;
}
