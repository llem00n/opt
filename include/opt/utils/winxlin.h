// *************************************************************************
// winxlin.h
// System Programming, part2: Programming language translator implementation
// Created by Porubaimikh Oleksandr on 11/30/23
// *************************************************************************

#ifndef OPT_UTILS_WIN_ANS_LIN_H
#define OPT_UTILS_WIN_ANS_LIN_H

#ifdef _WIN32
#define strncpy(dest, src, size) strncpy_s(dest, size, src)
#endif //_WIN32

#endif //OPT_UTILS_WIN_ANS_LIN_H
