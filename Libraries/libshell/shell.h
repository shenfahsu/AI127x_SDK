/*
 * This file is part of the libemb project.
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBRARIES_LIBSHELL_SHELL_H_
#define LIBRARIES_LIBSHELL_SHELL_H_

#include "radio.h"

// max number of character for a command line passed to the shell
#define SHELL_MAX_CMD_LINE		90

// max number of arguments passed with one command to the shell
#define SHELL_MAX_ARGS			3

// max number of character for a single argument form a command line passed to the shell
#define SHELL_MAX_ARG_LEN		MAX_LoraPayloadLength

// return code given when processing of a command line was OK
#define SHELL_PROCESS_OK		0

// ERROR maximum number of arguments was reached
#define SHELL_PROCESS_ERR_ARGS_MAX	0xfff0

// ERROR maximum number of chars for an argument was reached
#define SHELL_PROCESS_ERR_ARGS_LEN	0xfff1

// ERROR unknown command
#define SHELL_PROCESS_ERR_CMD_UNKN	0xfff2


// Single command argument
typedef struct {
	// Value representing the argument
	char 		val[ SHELL_MAX_ARG_LEN ];
} shell_cmd_arg;

// All arguments from a single command line
typedef struct {
	unsigned char	count;				// Number of arguments
	shell_cmd_arg	args[SHELL_MAX_ARGS];		// The arguments
} shell_cmd_args;


// Definition of a single shell command
typedef struct {
	const char 	*cmd;		// Name of the command
	const char	*desc;		// Description of the command

	int (*func)(shell_cmd_args *args);		// Functino called when executing the commmand
} shell_cmd;


// All shell commands knwon by the shell
typedef struct {
	unsigned char	count;		// Number of commands
	shell_cmd	*cmds;		// The commands
} shell_cmds;

/**
 * Return the length of a given string.
 *
 * @param[in]	str	string for which to calculate the length
 * @return		length of str
 */
int	shell_str_len( const char *str );

/**
 * Comapre str1 with given length len1 to str2 with given length len2.
 *
 * @param[in] 	str1	first string
 * @param[in] 	str2	second string
 * @param[in] 	len1	length of first string
 * @param[in] 	len2	length of second string
 * @return	0 if str1 euqals str2, 1 if len1 != len2, 2 if str1 != str2
 */
int	shell_str_cmp( const char *str1, const char *str2, int len1, int len2 );

/**
 * Parse the integer value from str and return it.
 *
 * @param[in]	str from which to parse the integer value.
 * @return	the integer value of str
 */
int	shell_parse_int( const char *str );

int	shell_arg_parser( const char *cmd_line, int len,  shell_cmd_args *args );

/**
 * Process a command line string given in cmd_line against the
 * commands given by cmds. If the command form cmd_line matches
 * against a command string defined in cmds, the function callback
 * for that command is executet.
 * <br/>
 * Note: the arguments form the command line are passed to the command
 * function, but the command function is responsible for checkeing the arguemts.
 *
 * @param[in]	*cmds	pointer to shell commands structure
 * @param[in]	*cmd_line	pointer to command line string
 * @return 	SHELL_PROCESS_OK if command and arguments where understood,
 * 			SHELL_PROCESS_ERR_ARGS_MAX if to many arguments are given,
 * 			SHELL_PROCESS_ERR_ARGS_LEN if an argument string was too long,
 * 			SHELL_PROCESS_ERR_CMD_UNK if the command was unknown
 */
//int	shell_process_cmds( shell_cmds *cmds, const char *cmd_line );
int	shell_process_cmds( const shell_cmd *cmd, unsigned char cmds, const char *cmd_line );

/**
 * Process a command line. For details see {@link shell_process_cmds}.
 * This method has to be implemented by a specific shell. The implementation
 * must pass a valid {@link shell_cmds} struct to {@link shell_process_cmds}.
 *
 * @param[in]	*cmd_line see {@link shell_process_cmds}
 * @return 	see {@link shell_process_cmds}
 */
// int		shell_process( char *cmd_line );

#endif		// LIBRARIES_LIBSHELL_SHELL_H_
