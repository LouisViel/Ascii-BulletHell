#pragma once

class Random
{
public:
	static void init();
	static int value();
	static char sign();

	static int valueInt();
	static int range(int min, int max);

	static double valueDouble();
	static double range(double min, double max);

private:
	Random() = delete;
	~Random() = delete;
};