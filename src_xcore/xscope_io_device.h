// Copyright (c) 2020, XMOS Ltd, All rights reserved
#ifndef XSCOPE_IO_DEVICE_H_
#define XSCOPE_IO_DEVICE_H_

#include <xcore/chanend.h>
#include <stddef.h>
#include "xscope_io_common.h"

typedef struct{
    char filename[MAX_FILENAME_LEN + 1];
    xscope_file_mode_t mode;
    unsigned index;
} xscope_file_t;


/******************************************************************************
 * xscope_io_init
 *
 * This opens the input and output files on the host and also initialises the
 * channel end for use later when reading data from host to device.
 * This must be called before attempting to read or write.
 *
 * @param   xscope_end is the app side channel end connected xscope_host_data()
 *          task in the top level application.
 * @return  void    
 ******************************************************************************/
void xscope_io_init(chanend_t xscope_end);

/******************************************************************************
 * xscope_open_files
 *
 * This opens the input and output files on the host and also initialises the
 * channel end for use later when reading data from host to device.
 * This must be called before attempting to read or write.
 *
 * @param   read_file_name to open on host
 * @param   write_file_name to open on host
 * @return  an initialised xscope_file_handle  
 ******************************************************************************/
xscope_file_t xscope_open_file(char* filename, char* attributes);

/******************************************************************************
 * xscope_fread
 *
 * Reads a number of bytes into the buffer provided by the application.
 * It sends a command to the host app which responds with an upload of the
 * requested data from the file. Each read is contiguous from the previous read
 *
 * @param   buffer that will be written the file read 
 * @param   n_bytes_to_read
 * @return  number of bytes actually read. Will be zero if EOF already hit.    
 ******************************************************************************/
size_t xscope_fread(uint8_t *buffer, size_t n_bytes_to_read, xscope_file_t *xscope_io_handle);

/******************************************************************************
 * xscope_fwrite
 *
 * Writes a number of bytes from the buffer provided by the application.
 *
 * @param   buffer that will be read and sent to be written on the host 
 * @param   n_bytes_to_read
 * @return  void    
 ******************************************************************************/
void xscope_fwrite(uint8_t *buffer, size_t n_bytes_to_write, xscope_file_t *xscope_io_handle);

/******************************************************************************
 * xscope_close_files
 *
 * Closes both the read and write file on the host.
 * This must be called at the end of device application.
 *
 * @return  void    
 ******************************************************************************/
void xscope_close_files(void);


#endif