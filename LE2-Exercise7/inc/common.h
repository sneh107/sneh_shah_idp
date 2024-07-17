/*******************************************************************************
 * Copyright(c) 2024, Volansys Technologies
 *
 * Description:
 * @file common.h
 * @brief Common header file for the chat application.
 *
 * This file includes common library headers and definitions used by both the client and server programs.
 * It defines constants for the port number, buffer size, and maximum name length.
 *
 * Author       - Sneh Shah
 *
 *******************************************************************************
 *
 * History
 *
 * Jul/01/2024, Sneh Shah, Created
 *
 ******************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>

#define PORT 7777
#define BUFFER_SIZE 1024
#define NAME_LEN 32

#endif