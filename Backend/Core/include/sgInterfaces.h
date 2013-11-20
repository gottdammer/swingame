//
//  sgInterfaces.h
//  sgsdl2
//
//  Created by Andrew Cain on 19/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sgsdl2_sgInterfaces_h
#define sgsdl2_sgInterfaces_h

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus

#include "sgBackendTypes.h"

extern "C" {
#endif
    
    typedef unsigned char byte;
    typedef enum sg_interface_features
    {
        SGV_NONE = 0x00,
        SGV_INIT = 0x01
    } sg_interface_version;
    
    typedef void (sg_empty_procedure)( void );
    typedef void (sg_drawing_surface_proc)( sg_drawing_surface * );
    typedef void (sg_single_uint32param_proc)( unsigned int ms );
    typedef void (sg_drawing_surface_clr_proc)( sg_drawing_surface *, float r, float g, float b, float a );

    typedef sg_drawing_surface  (sg_new_surface_fn)(const char *title, int width, int height);

    
    //
    // Utility relation functions
    //
    // - delay = Function to delay by a specified number of milliseconds.
    //
    typedef struct sg_utils_interface
    {
        sg_single_uint32param_proc *delay;
        
    } sg_utils_interface;
    
    
    //
    // Graphics related functions.
    //
    // - open_window = Open a new window and return its details.
    // - close_drawing_surface = Close a previously open drawing surface (window/bitmap/etc)
    // - refresh_window = Present window to user
    // - clear_drawing_surface = Clear the screen or bitmap
    //
    typedef struct sg_graphics_interface
    {
        sg_new_surface_fn       * open_window;
        
        sg_drawing_surface_proc * close_drawing_surface;
        sg_drawing_surface_proc * refresh_window;
        
        sg_drawing_surface_clr_proc * clear_drawing_surface;

    } sg_graphics_interface;
    
    
    //
    // All sg functions.
    //
    // - has_error (data) = is there currently an error
    // - current_error (data) = A pointer to the current error message. This error
    //                          is managed by the driver and must not be freed by
    //                          the driver's user.
    // - graphics (data) = Functions associated with windows and drawing
    // - utils (data) = Functions associated with utilities
    //
    // - init = The init procedure is called when the SwinGame starts and should
    //          be used to initialise the underlying system.
    //
    typedef struct sg_interface
    {
        bool has_error;
        const char *    current_error;

        //
        // function pointers by functionality
        //
        sg_graphics_interface graphics;
        sg_utils_interface utils;
        
        sg_empty_procedure *init;
    } sg_interface;

    
    //
    // All sg backends need to implement a load function that can be
    // called to load the function pointers for the frontend to use.
    //
    sg_interface * sg_load();

    
#ifdef __cplusplus
}
#endif

#endif