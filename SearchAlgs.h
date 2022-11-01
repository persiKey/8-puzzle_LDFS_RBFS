#pragma once
#include "General.h"

constexpr int LDFS_DEPTH_LIMIT = 22;

void LimitedDFS(State s);

void RecursiveBestFS(State s);

Result RecursiveLDFS(info& info);

int h(State& s);

Result RBSF(info& info, int limit, int* prev_best);
