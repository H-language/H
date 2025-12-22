////////////////////////////////////////////////////////////////
//
//  Hydrogen Language (H-lang)
//
//  author(s):
//  ENDESGA - https://x.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/H
//  2025 - CC0 - FOSS forever
//

#pragma once

////////////////////////////////
/// include(s)

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

////////////////////////////////
/// version

#define H_VERSION_MAJOR 0
#define H_VERSION_MINOR 1
#define H_VERSION_PATCH 0
#define H_VERSION AS_BYTES( H_VERSION_MAJOR ) "." AS_BYTES( H_VERSION_MINOR ) "." AS_BYTES( H_VERSION_PATCH )

////////////////////////////////
/// OS specific

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_UNKNOWN 0

#if defined( __linux__ )
	#undef OS_LINUX
	#define OS_LINUX 1
	#define OS_NAME "Linux"
	#if __BYTE_ORDER == __LITTLE_ENDIAN
		#define IS_BIG_ENDIAN 0
	#elif __BYTE_ORDER == __BIG_ENDIAN
		#define IS_BIG_ENDIAN 1
	#endif
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <dirent.h>
	#include <time.h>
	#include <fcntl.h>
	#include <pthread.h>
	#include <unistd.h>

#elif defined( _WIN32 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
	#define OS_NAME "Windows"
	#define IS_BIG_ENDIAN 0
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>

#elif defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
	#define OS_NAME "macOS"
	#define IS_BIG_ENDIAN 0

#else
	#undef OS_UNKNOWN
	#define OS_UNKNOWN 1
	#define OS_NAME "unknown"
#endif

////////////////////////////////
/// compiler specific

#define COMPILER_GCC 0
#define COMPILER_TCC 0
#define COMPILER_CLANG 0
#define COMPILER_MSVC 0
#define COMPILER_UNKNOWN 0

#if defined( __clang__ )
	#undef COMPILER_CLANG
	#define COMPILER_CLANG 1
	#define COMPILER_NAME "Clang"

#elif defined( __TINYC__ )
	#undef COMPILER_TCC
	#define COMPILER_TCC 1
	#define COMPILER_NAME "TCC"

#elif defined( __GNUC__ )
	#undef COMPILER_GCC
	#define COMPILER_GCC 1
	#define COMPILER_NAME "GCC"

#elif defined( _MSC_VER )
	#undef COMPILER_MSVC
	#define COMPILER_MSVC 1
	#define COMPILER_NAME "MSVC"

#else
	#undef COMPILER_UNKNOWN
	#define COMPILER_UNKNOWN 1
	#define COMPILER_NAME "unknown"
#endif

////////////////////////////////
/// scoped defines

#define START_DEF do
#define END_DEF while( 0 )

#define REQUIRE_SEMICOLON START_DEF {} END_DEF

////////////////////////////////
/// magic macros

#define _EVAL( ARGS... ) ARGS
#define EVAL( ARGS... ) _EVAL( ARGS )
#define _JOIN( A, B... ) A##B
#define JOIN( A, B... ) _JOIN( A, B )

#define SKIP_ARG( _, ARGS... ) ARGS

#define GET_ARG0( ... )
#define GET_ARG1( a, ... ) a
#define GET_ARG2( a, b, ... ) b
#define GET_ARG3( a, b, c, ... ) c
#define GET_ARG4( a, b, c, d, ... ) d
#define GET_ARG5( a, b, c, d, e, ... ) e
#define GET_ARG6( a, b, c, d, e, f, ... ) f
#define GET_ARG7( a, b, c, d, e, f, g, ... ) g
#define GET_ARG8( a, b, c, d, e, f, g, h, ... ) h
#define GET_ARG9( a, b, c, d, e, f, g, h, i, ... ) i
#define GET_ARG10( a, b, c, d, e, f, g, h, i, j, ... ) j
#define GET_ARG11( a, b, c, d, e, f, g, h, i, j, k, ... ) k
#define GET_ARG12( a, b, c, d, e, f, g, h, i, j, k, l, ... ) l
#define GET_ARG13( a, b, c, d, e, f, g, h, i, j, k, l, m, ... ) m
#define GET_ARG14( a, b, c, d, e, f, g, h, i, j, k, l, m, n, ... ) n
#define GET_ARG15( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, ... ) o
#define GET_ARG16( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, ... ) p
#define GET_ARG17( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ... ) q

#define COMMA ,

#define _PASTE_IF_ARGS_EVAL( CODE, ARGS... ) GET_ARG2( ARGS, EVAL CODE )
#define _PASTE_IF_ARGS( CODE, ARGS... ) _PASTE_IF_ARGS_EVAL( CODE, GET_ARG1 ARGS( COMMA ) )
#define PASTE_IF_ARGS( CODE, ARGS... ) _PASTE_IF_ARGS( ( CODE ), GET_ARG1( ARGS ) )

#define COMMA_IF_ARGS( ARGS... ) PASTE_IF_ARGS( COMMA, ARGS )

#define _COUNT_ARGS_EVAL( ARGS... ) GET_ARG17( ARGS, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 )
#define COUNT_ARGS( ARGS... ) _COUNT_ARGS_EVAL( ARGS COMMA_IF_ARGS( ARGS ) 16 )

#define _AS_BYTES( VALUE ) #VALUE
#define AS_BYTES( VALUE ) _AS_BYTES( VALUE )

////////
// default arguments

#define _DEFAULT_EVAL( ARGS... ) GET_ARG1( ARGS )
#define DEFAULT( DEF, ARGS... ) _DEFAULT_EVAL( ARGS COMMA_IF_ARGS( ARGS ) DEF )
#define _DEFAULTS_0( DEFS, ... )
#define _DEFAULTS_1( DEFS, ARGS... ) DEFAULT( GET_ARG1 DEFS, ARGS )
#define _DEFAULTS_2( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_1( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_3( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_2( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_4( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_3( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_5( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_4( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_6( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_5( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_7( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_6( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_8( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_7( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_9( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_8( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_10( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_9( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_11( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_10( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_12( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_11( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_13( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_12( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_14( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_13( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_15( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_14( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_16( DEFS, ARGS... ) _DEFAULTS_1( DEFS, ARGS ) , _DEFAULTS_15( ( SKIP_ARG DEFS ), SKIP_ARG( ARGS ) )
#define _DEFAULTS_MAKE( COUNT, DEFS, ARGS... ) JOIN( _DEFAULTS_, COUNT ) ( DEFS, ARGS )
#define DEFAULTS( DEFS, ARGS... ) _DEFAULTS_MAKE( COUNT_ARGS DEFS, DEFS, ARGS )

////////
// symbol chains

#define _CHAIN_0( MODE, L, R, MID, ARGS... ) ARGS
#define _CHAIN_1_EMPTY( L, R, MID, ARG ) L ARG R
#define _CHAIN_1_PAREN( L, R, MID, ARG ) ( L ARG R )
#define _CHAIN_1( MODE, L, R, MID, ARG ) _CHAIN_1_##MODE( L, R, MID, ARG )
#define _CHAIN_JOIN( MODE, L, R, MID, ARG, NEXT ) _CHAIN_1( MODE, L, R, MID, ARG ) MID NEXT
#define _CHAIN_2( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_1( MODE, L, R, MID, ARGS ) )
#define _CHAIN_3( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_2( MODE, L, R, MID, ARGS ) )
#define _CHAIN_4( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_3( MODE, L, R, MID, ARGS ) )
#define _CHAIN_5( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_4( MODE, L, R, MID, ARGS ) )
#define _CHAIN_6( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_5( MODE, L, R, MID, ARGS ) )
#define _CHAIN_7( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_6( MODE, L, R, MID, ARGS ) )
#define _CHAIN_8( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_7( MODE, L, R, MID, ARGS ) )
#define _CHAIN_9( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_8( MODE, L, R, MID, ARGS ) )
#define _CHAIN_10( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_9( MODE, L, R, MID, ARGS ) )
#define _CHAIN_11( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_10( MODE, L, R, MID, ARGS ) )
#define _CHAIN_12( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_11( MODE, L, R, MID, ARGS ) )
#define _CHAIN_13( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_12( MODE, L, R, MID, ARGS ) )
#define _CHAIN_14( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_13( MODE, L, R, MID, ARGS ) )
#define _CHAIN_15( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_14( MODE, L, R, MID, ARGS ) )
#define _CHAIN_16( MODE, L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( MODE, L, R, MID, ARG, _CHAIN_15( MODE, L, R, MID, ARGS ) )
#define _CHAIN_MAKE( COUNT, MODE, L, R, MID, ARGS... ) JOIN( _CHAIN_, COUNT ) ( MODE, L, R, MID, ARGS )

#define CHAIN( L, R, MID, ARGS... ) _CHAIN_MAKE( COUNT_ARGS( ARGS ), EMPTY, L, R, MID, ARGS )
#define CHAIN_PAREN( L, R, MID, ARGS... ) _CHAIN_MAKE( COUNT_ARGS( ARGS ), PAREN, L, R, MID, ARGS )

////////////////////////////////
/// prefixes

#define temp register
#define perm static
#define global perm

#if OS_LINUX
	#define cache_align __attribute__( ( aligned( 64 ) ) )
#else
	#define cache_align __declspec( align( 64 ) )
#endif

////////////////////////////////
/// references/values

#define ref *

#define type_from( TYPE... ) typedef TYPE
#define ref_of( VAR... ) ( & ( VAR ) )
#define val_of( REF... ) ( * ( REF ) )
#define to( TYPE, VAL... ) ( TYPE ) ( VAL )
#define cast( TYPE, VAR... ) val_of( to( TYPE ref, ref_of( VAR ) ) )

#define anon void
#define nothing to( anon ref, 0 )

#define size_of( TYPE... ) sizeof( TYPE )
#define type_of( VAR... ) typeof( VAR )
#define type_of_ref( REF... ) type_of( val_of( to( type_of( REF ), nothing ) ) )

////////////////////////////////
/// functions

#define embed perm inline
#define fn embed anon
#define out return

#define fn_ref( OUTPUT, NAME, ARG_TYPES... ) OUTPUT( ref NAME ) ( ARG_TYPES )
#define fn_type( OUTPUT, ARG_TYPES... ) type_from( type_of( fn_ref( DEFAULT( anon, OUTPUT ),, ARG_TYPES ) ) )

////////////////////////////////
/// flags

type_from( _Bool ) flag;
#define flag( ARGS... ) to( flag, !! ( ARGS ) )
#define yes 1
#define no 0
#define flip( FLAG ) FLAG ^= 1

////////
// flag logic

#define not !
#define and &&
#define or ||
#define xor ^
#define mod %
#define is ==
#define isnt !=
#define is_even mod 2 is 0
#define is_odd mod 2 isnt 0

#define pick( IF_YES, THEN_THIS, ELSE_THIS ) ( ( IF_YES ) ? ( THEN_THIS ) : ( ELSE_THIS ) )
#define PICK_0( THEN_THIS, ELSE_THIS ) ELSE_THIS
#define PICK_1( THEN_THIS, ELSE_THIS ) THEN_THIS
#define PICK( IF_1, THEN_THIS, ELSE_THIS... ) JOIN( PICK_, IF_1 ) ( THEN_THIS, ELSE_THIS )

#define if_nothing( ARG... ) if( ARG is nothing )
#define if_something( ARG... ) if( ARG isnt nothing )

#define any( ARGS... ) ( CHAIN_PAREN(,, or, ARGS ) )
#define all( ARGS... ) ( CHAIN_PAREN(,, and, ARGS ) )
#define none( ARGS... ) ( not any( ARGS ) )
#define not_all( ARGS... ) ( not all( ARGS ) )

#define if_any( ARGS... ) if any( ARGS )
#define if_all( ARGS... ) if all( ARGS )
#define if_none( ARGS... ) if none( ARGS )
#define if_not_all( ARGS... ) if not_all( ARGS )

////////////////////////////////
/// loops

#define loop for( ;; )
#define next continue
#define skip break
#define jump goto
#define until( ARGS... ) while( not( ARGS ) )

////////
// with/when jump-tree

#define with switch
#define when( ARGS... ) CHAIN( case, :,, ARGS )
#define other default:

////////
// range (inclusive)

#define _range( POS_NAME, FROM, TO, STEP, SYMBOL_COMPARE, SYMBOL_STEP ) for( temp i8 POS_NAME = i8( FROM ); POS_NAME SYMBOL_COMPARE i8( TO ); POS_NAME SYMBOL_STEP i8( STEP ) )

#define range_step( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, <=, += )
#define range_step_inv( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, >=, -= )

#define range( POS_NAME, FROM, TO ) range_step( POS_NAME, FROM, TO, 1 )
#define range_inv( POS_NAME, FROM, TO ) range_step_inv( POS_NAME, FROM, TO, 1 )

#define range_grid( X_NAME, Y_NAME, X_FROM, X_TO, Y_FROM, Y_TO ) range( Y_NAME, Y_FROM, Y_TO ) range( X_NAME, X_FROM, X_TO )

////////
// iterate (exclusive)

#define iter_step( POS_NAME, SIZE, STEP ) _range( POS_NAME, 0, SIZE, STEP, <, += )
#define iter_step_inv( POS_NAME, SIZE, STEP ) _range( POS_NAME, SIZE, 0, STEP, >, -= )

#define iter( POS_NAME, SIZE ) _range( POS_NAME, 0, SIZE, 1, <, += )
#define iter_inv( POS_NAME, SIZE ) _range( POS_NAME, SIZE - 1, 0, 1, >=, -= )

#define iter_grid( X_NAME, Y_NAME, WIDTH, HEIGHT ) iter( Y_NAME, HEIGHT ) iter( X_NAME, WIDTH )

#define _repeat( N_TIMES, COUNTER ) iter( JOIN( _REP_, COUNTER ), N_TIMES )
#define repeat( N_TIMES ) _repeat( N_TIMES, __COUNTER__ )

#define _once( _ONCE_ )\
	perm flag _ONCE_ = yes;\
	if( _ONCE_ and( _ONCE_ = no, yes ) )
#define once _once( JOIN( _ONCE_, __COUNTER__ ) )

////////
// conditionals

#define while_any( ARGS... ) while any( ARGS )
#define while_all( ARGS... ) while all( ARGS )
#define while_none( ARGS... ) while none( ARGS )
#define while_not_all( ARGS... ) while not_all( ARGS )

#define skip_if( ARG... ) if( ARG ) skip
#define skip_if_nothing( ARG... ) if_nothing( ARG ) skip
#define skip_if_something( ARG... ) if_something( ARG ) skip
#define skip_if_any( ARGS... ) if_any( ARGS ) skip
#define skip_if_all( ARGS... ) if_all( ARGS ) skip
#define skip_if_none( ARGS... ) if_none( ARGS ) skip
#define skip_if_not_all( ARGS... ) if_not_all( ARGS ) skip

#define jump_if( ARG... ) if( ARG ) jump
#define jump_if_nothing( ARG... ) if_nothing( ARG ) jump
#define jump_if_something( ARG... ) if_something( ARG ) jump
#define jump_if_any( ARGS... ) if_any( ARGS ) jump
#define jump_if_all( ARGS... ) if_all( ARGS ) jump
#define jump_if_none( ARGS... ) if_none( ARGS ) jump
#define jump_if_not_all( ARGS... ) if_not_all( ARGS ) jump

#define next_if( ARG... ) if( ARG ) next
#define next_if_nothing( ARG... ) if_nothing( ARG ) next
#define next_if_something( ARG... ) if_something( ARG ) next
#define next_if_any( ARGS... ) if_any( ARGS ) next
#define next_if_all( ARGS... ) if_all( ARGS ) next
#define next_if_none( ARGS... ) if_none( ARGS ) next
#define next_if_not_all( ARGS... ) if_not_all( ARGS ) next

#define out_if( ARG... ) if( ARG ) out
#define out_if_nothing( ARG... ) if_nothing( ARG ) out
#define out_if_something( ARG... ) if_something( ARG ) out
#define out_if_any( ARGS... ) if_any( ARGS ) out
#define out_if_all( ARGS... ) if_all( ARGS ) out
#define out_if_none( ARGS... ) if_none( ARGS ) out
#define out_if_not_all( ARGS... ) if_not_all( ARGS ) out

////////////////////////////////
/// value types

type_from( char ) byte;
#define byte( VAL ) to( byte, VAL )
#define size_of_bytes( BYTES ) ( size_of( BYTES ) - 1 )

////////
// bits

#define n_to_bits( N ) pick( ( N ) <= 1, 1, ( 32 - __builtin_clz( ( N ) - 1 ) ) )

////////
// natural 1/2/4/8, integer 1/2/4/8, rational 4/8

// 1 byte
type_from( uint8_t ) n1;
#define n1( VAL ) to( n1, VAL )
#define min_n1 0
#define max_n1 UINT8_MAX
//
type_from( int8_t ) i1;
#define i1( VAL ) to( i1, VAL )
#define min_i1 INT8_MIN
#define max_i1 INT8_MAX

// 2 bytes
type_from( uint16_t ) n2;
#define n2( VAL ) to( n2, VAL )
#define min_n2 0
#define max_n2 UINT16_MAX
//
type_from( int16_t ) i2;
#define i2( VAL ) to( i2, VAL )
#define min_i2 INT16_MIN
#define max_i2 INT16_MAX

// 4 bytes
type_from( uint32_t ) n4;
#define n4( VAL ) to( n4, VAL )
#define min_n4 0
#define max_n4 UINT32_MAX
//
type_from( int32_t ) i4;
#define i4( VAL ) to( i4, VAL )
#define min_i4 INT32_MIN
#define max_i4 INT32_MAX
//
type_from( float ) r4;
#define r4( VAL ) to( r4, VAL )

// 8 bytes
type_from( uint64_t ) n8;
#define n8( VAL ) to( n8, VAL )
#define min_n8 0
#define max_n8 UINT64_MAX
//
type_from( int64_t ) i8;
#define i8( VAL ) to( i8, VAL )
#define min_i8 INT64_MIN
#define max_i8 INT64_MAX
//
type_from( double ) r8;
#define r8( VAL ) to( r8, VAL )

////////////////////////////////
/// function output state

type_from( i4 ) out_state;
#define success 0
#define failure 1
#define warning 2

////////////////////////////////
/// function arguments

#define arg_list va_list
#define args_init( ARG_LIST, BEFORE_ELLIPSIS ) va_start( ARG_LIST, BEFORE_ELLIPSIS )
#define args_end( ARG_LIST ) va_end( ARG_LIST )
#define args_copy( FROM, TO ) va_copy( TO, FROM )

#define _args_next_byte int
#define _args_next_n1 unsigned int
#define _args_next_i1 signed int
#define _args_next_n2 unsigned int
#define _args_next_i2 signed int
#define _args_next_n4 unsigned int
#define _args_next_i4 signed int
#define _args_next_r4 double
#define _args_next_n8 unsigned long long
#define _args_next_i8 signed long long
#define _args_next_r8 double
#define _args_next_ref long ref
#define args_next( ARGS, TYPE ) va_arg( ARGS, _args_next_##TYPE )

////////////////////////////////
/// bytes (a byte ref)

#define is_letter( BYTE ) ( ( ( n4( BYTE ) | 0x20 ) - 'a' ) < 26 )
#define is_number( BYTE ) ( ( n4( BYTE ) - '0' ) < 10 )

#define KB( KILOBYTES ) ( ( KILOBYTES ) * 1000 )
#define MB( MEGABYTES ) ( ( MEGABYTES ) * 1000000 )
#define GB( GIGABYTES ) ( ( GIGABYTES ) * 1000000000 )

#define KiB( KIBIBYTES ) ( ( KIBIBYTES ) << 10 )
#define MiB( MEBIBYTES ) ( ( MEBIBYTES ) << 20 )
#define GiB( GIBIBYTES ) ( ( GIBIBYTES ) << 30 )

#define new_bytes( AMOUNT... ) malloc( DEFAULT( 1, AMOUNT ) )
#define delete_bytes delete_ref
#define duplicate_bytes( BYTES ) strdup( BYTES )

#define bytes_resize( REF, NEW_SIZE... ) realloc( REF, DEFAULT( 1, NEW_SIZE ) )

#define bytes_copy( TO_REF, FROM_REF, FROM_SIZE ) memcpy( TO_REF, FROM_REF, FROM_SIZE )
#define bytes_copy_until( TO_REF, FROM_REF, CHAR, MAX_SIZE ) memccpy( TO_REF, FROM_REF, CHAR, MAX_SIZE )
#define bytes_copy_until_any( TO_REF, FROM_REF, DELIMS ) memcpy( TO_REF, FROM_REF, strcspn( FROM_REF, DELIMS ) )
#define bytes_paste( TO_REF, FROM_REF ) strcpy( TO_REF, FROM_REF )
#define bytes_move( REF, POSITION, SIZE, MOVE_AMOUNT ) memmove( ( REF ) + ( POSITION ) + ( MOVE_AMOUNT ), ( REF ) + ( POSITION ), ( SIZE ) )
#define bytes_fill( REF, VAL, SIZE ) memset( REF, VAL, SIZE )
#define bytes_clear( REF, SIZE ) bytes_fill( REF, 0, SIZE )
#define bytes_compare( A, B, AMOUNT ) memcmp( A, B, AMOUNT )
#define bytes_measure( REF ) strlen( REF )
#define bytes_end( BYTES ) val_of( BYTES ) = eof_byte

////////
// auto-move variations

#define bytes_copy_move( TO_REF, FROM_REF, FROM_SIZE )\
	START_DEF\
	{\
		bytes_copy( TO_REF, FROM_REF, FROM_SIZE );\
		TO_REF += FROM_SIZE;\
	}\
	END_DEF

#define bytes_paste_move( TO_REF, FROM_REF )\
	START_DEF\
	{\
		temp byte const ref const _FROM_REF = FROM_REF;\
		temp n2 const _PASTE_SIZE = bytes_measure( _FROM_REF );\
		bytes_copy_move( TO_REF, _FROM_REF, _PASTE_SIZE );\
	}\
	END_DEF

#define bytes_set_move( TO_REF, BYTE ) val_of( TO_REF++ ) = BYTE

#define bytes_newline_move( TO_REF ) bytes_set_move( TO_REF, newline_byte )
#define bytes_separator_move( TO_REF ) bytes_set_move( TO_REF, separator_byte )

////////////////////////////////
/// allocated references/bytes

#define new_ref( TYPE, AMOUNT... ) to( TYPE ref, calloc( DEFAULT( 1, AMOUNT ), size_of( TYPE ) ) )
#define delete_ref( REF ) if_something( REF ) free( REF )

embed anon ref const _ref_resize( anon ref const r, n8 const type_size, n8 const old_count, n8 const new_count )
{
	temp anon ref const new_ptr = realloc( r, type_size * new_count );
	if( new_ptr isnt nothing and new_count > old_count )
	{
		bytes_clear( to( byte ref, new_ptr ) + ( type_size * old_count ), type_size * ( new_count - old_count ) );
	}
	out new_ptr;
}
#define ref_resize( REF, OLD_COUNT, NEW_COUNT ) _ref_resize( REF, size_of( type_of_ref( REF ) ), OLD_COUNT, NEW_COUNT )

////////////////////////////////
/// new declarations

#define packed __attribute__( ( packed ) )
#define variant struct

////////
// type

#define _type_make( NAME, REF, EXTRA... )\
	type_from( variant NAME REF ) NAME;\
	EXTRA;\
	variant NAME
#define type( NAME ) _type_make( NAME, )

#define make( TYPE, ELEMENT_VALUES... ) ( ( TYPE ) { ELEMENT_VALUES } )

////////
// object

#define object( NAME ) _type_make( NAME, ref, fn_type(, NAME this ) NAME##_fn )
#define object_fn( OBJECT, FN, ARGS... )\
	fn OBJECT##_##FN( OBJECT const this COMMA_IF_ARGS( ARGS ) ARGS )
#define new_object_fn( OBJECT, ARGS... )\
	embed OBJECT new_##OBJECT( ARGS )
#define delete_object_fn( OBJECT, ARGS... )\
	fn delete_##OBJECT( OBJECT const this COMMA_IF_ARGS( ARGS ) ARGS )

#define call( OBJECT, FN, ARGS... ) if( OBJECT isnt nothing and OBJECT->FN isnt nothing ) OBJECT->FN( OBJECT COMMA_IF_ARGS( ARGS ) ARGS )

#define type_of_object( OBJECT ) variant OBJECT

#define new_object( OBJECT ) new_ref( type_of_object( OBJECT ) )
#define delete_object( OBJECT ) delete_ref( OBJECT )

////////
// fusion

#define fusion( NAME )\
	type_from( union NAME ) NAME;\
	union NAME

////////
// group

#define group( NAME, TYPE... )\
	type_from( DEFAULT( byte, TYPE ) ) NAME;\
	enum NAME

////////////////////////////////
/// byte conversion

#define _BYTES_ADD_BUFFER( BYTES )\
	byte buffer[ BYTES ];\
	byte ref p = buffer + BYTES

#define _BYTES_ADD_NEGATIVE( TO_REF, VAL )\
	if( VAL < 0 )\
	{\
		VAL = -VAL;\
		bytes_set_move( TO_REF, '-' );\
	}

#define _BYTES_ADD_N( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 count = 0;\
		do\
		{\
			val_of( --p ) = ( VAL mod 10 ) + '0';\
			VAL /= 10;\
			++count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, p, count );\
	}\
	END_DEF

#define _BYTES_ADD_I( TO_REF, VAL )\
	START_DEF\
	{\
		_BYTES_ADD_NEGATIVE( TO_REF, VAL );\
		_BYTES_ADD_N( TO_REF, VAL );\
	}\
	END_DEF

#define bytes_n1_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 3 );\
		_BYTES_ADD_N( TO_REF, _val );\
	}\
	END_DEF

#define bytes_n2_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 5 );\
		_BYTES_ADD_N( TO_REF, _val );\
	}\
	END_DEF

#define bytes_n4_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 10 );\
		_BYTES_ADD_N( TO_REF, _val );\
	}\
	END_DEF

#define bytes_n8_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 20 );\
		_BYTES_ADD_N( TO_REF, _val );\
	}\
	END_DEF

#define bytes_i1_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp i1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 4 );\
		_BYTES_ADD_I( TO_REF, _val );\
	}\
	END_DEF

#define bytes_i2_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp i2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 6 );\
		_BYTES_ADD_I( TO_REF, _val );\
	}\
	END_DEF

#define bytes_i4_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp i4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 11 );\
		_BYTES_ADD_I( TO_REF, _val );\
	}\
	END_DEF

#define bytes_i8_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp i8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 21 );\
		_BYTES_ADD_I( TO_REF, _val );\
	}\
	END_DEF

#define _BYTES_ADD_R( TO_REF, VAL, N )\
	START_DEF\
	{\
		temp i##N int_part = to( i##N, VAL );\
		temp r##N frac_part = VAL - int_part;\
		_BYTES_ADD_N( TO_REF, int_part );\
		bytes_set_move( TO_REF, '.' );\
		iter( i, N )\
		{\
			frac_part *= 10;\
			temp n1 const digit = ( n1 ) frac_part;\
			bytes_set_move( TO_REF, '0' + digit );\
			frac_part -= digit;\
		}\
	}\
	END_DEF

#define bytes_r4_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp r4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 32 );\
		_BYTES_ADD_NEGATIVE( TO_REF, _val );\
		_BYTES_ADD_R( TO_REF, _val, 4 );\
	}\
	END_DEF

#define bytes_r8_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp r8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 64 );\
		_BYTES_ADD_NEGATIVE( TO_REF, _val );\
		_BYTES_ADD_R( TO_REF, _val, 8 );\
	}\
	END_DEF

#define _BYTES_ADD_OCTAL( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 count = 0;\
		do\
		{\
			val_of( --p ) = ( VAL & 7 ) + '0';\
			VAL >>= 3;\
			++count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, p, count );\
	}\
	END_DEF

#define bytes_octal_n1_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 3 );\
		_BYTES_ADD_OCTAL( TO_REF, _val );\
	}\
	END_DEF

#define bytes_octal_n2_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 6 );\
		_BYTES_ADD_OCTAL( TO_REF, _val );\
	}\
	END_DEF

#define bytes_octal_n4_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 11 );\
		_BYTES_ADD_OCTAL( TO_REF, _val );\
	}\
	END_DEF

#define bytes_octal_n8_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 22 );\
		_BYTES_ADD_OCTAL( TO_REF, _val );\
	}\
	END_DEF

#define _BYTES_ADD_HEX( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 count = 0;\
		do\
		{\
			val_of( --p ) = "0123456789ABCDEF"[ VAL & 0xF ];\
			VAL >>= 4;\
			++count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, p, count );\
	}\
	END_DEF

#define bytes_hex_n1_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 2 );\
		_BYTES_ADD_HEX( TO_REF, _val );\
	}\
	END_DEF

#define bytes_hex_n2_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 4 );\
		_BYTES_ADD_HEX( TO_REF, _val );\
	}\
	END_DEF

#define bytes_hex_n4_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 8 );\
		_BYTES_ADD_HEX( TO_REF, _val );\
	}\
	END_DEF

#define bytes_hex_n8_move( TO_REF, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 16 );\
		_BYTES_ADD_HEX( TO_REF, _val );\
	}\
	END_DEF

////////////////////////////////
/// terminal print

#define print( BYTES ) fputs( BYTES, stdout )
#define print_count( BYTES, SIZE ) fwrite( BYTES, 1, SIZE, stdout )
#define print_show() fflush( stdout )

#define newline "\n"
#define newline_byte '\n'

#define separator PICK( OS_LINUX, "/", "\\" )
#define separator_byte PICK( OS_LINUX, '/', '\\' )

#define tab "\t"
#define tab_byte '\t'

#define eof "\0"
#define eof_byte '\0'

#define print_newline() print_count( newline, 1 )
#define print_separator() print_count( separator, 1 )
#define print_tab() print_count( tab, 1 )

////////
// formats

#define format_reset "\033[0m"

#define format_bold "\033[1m"
#define format_dim "\033[2m"
#define format_italic "\033[3m"
#define format_underline "\033[4m"
#define format_blink "\033[5m"
#define format_reverse "\033[7m"
#define format_hidden "\033[8m"
#define format_strikethrough "\033[9m"

#define format_no_bold "\033[22m"
#define format_no_italic "\033[23m"
#define format_no_underline "\033[24m"
#define format_no_blink "\033[25m"
#define format_no_reverse "\033[27m"
#define format_no_hidden "\033[28m"
#define format_no_strikethrough "\033[29m"

#define format_rgb( R, G, B ) "\033[38;2;" #R ";" #G ";" #B "m"

#define format_black format_rgb( 0, 0, 0 )
#define format_white format_rgb( 255, 255, 255 )
#define format_red format_rgb( 255, 68, 68 )
#define format_yellow format_rgb( 255, 255, 68 )
#define format_green format_rgb( 68, 255, 68 )
#define format_cyan format_rgb( 68, 255, 255 )
#define format_blue format_rgb( 68, 68, 255 )
#define format_magenta format_rgb( 255, 68, 255 )
#define format_gray format_rgb( 119, 119, 119 )
#define format_dark_red format_rgb( 119, 34, 34 )
#define format_dark_yellow format_rgb( 119, 119, 34 )
#define format_dark_green format_rgb( 34, 119, 34 )
#define format_dark_cyan format_rgb( 34, 119, 119 )
#define format_dark_blue format_rgb( 34, 34, 119 )
#define format_dark_magenta format_rgb( 119, 34, 119 )
#define format_color_default "\033[39m"

#define format_bg_rgb( R, G, B ) "\033[48;2;" #R ";" #G ";" #B "m"

#define format_bg_black format_bg_rgb( 0, 0, 0 )
#define format_bg_white format_bg_rgb( 255, 255, 255 )
#define format_bg_red format_bg_rgb( 255, 68, 68 )
#define format_bg_yellow format_bg_rgb( 255, 255, 68 )
#define format_bg_green format_bg_rgb( 68, 255, 68 )
#define format_bg_cyan format_bg_rgb( 68, 255, 255 )
#define format_bg_blue format_bg_rgb( 68, 68, 255 )
#define format_bg_magenta format_bg_rgb( 255, 68, 255 )
#define format_bg_gray format_bg_rgb( 119, 119, 119 )
#define format_bg_dark_red format_bg_rgb( 119, 34, 34 )
#define format_bg_dark_yellow format_bg_rgb( 119, 119, 34 )
#define format_bg_dark_green format_bg_rgb( 34, 119, 34 )
#define format_bg_dark_cyan format_bg_rgb( 34, 119, 119 )
#define format_bg_dark_blue format_bg_rgb( 34, 34, 119 )
#define format_bg_dark_magenta format_bg_rgb( 119, 34, 119 )
#define format_bg_default "\033[49m"

////////
// print format

#define print_set_format( FORMAT ) print_count( format_##FORMAT, size_of( format_##FORMAT ) )

#define print_set_rgb( R, G, B ) print( format_rgb( R, G, B ) )
#define print_set_color( COLOR ) print_set_format( COLOR )
#define print_set_dark_color( COLOR ) print_set_format( dark_##COLOR )
#define print_unset_color() print_set_format( color_default )
#define print_set_bg_rgb( R, G, B ) print( format_bg_rgb( R, G, B ) )
#define print_set_bg_color( COLOR ) print_set_format( bg_##COLOR )
#define print_set_bg_dark_color( COLOR ) print_set_format( bg_dark_##COLOR )
#define print_unset_bg_color() print_set_format( bg_default )

#define print_set_bold() print_set_format( bold )
#define print_set_dim() print_set_format( dim )
#define print_set_italic() print_set_format( italic )
#define print_set_underline() print_set_format( underline )
#define print_set_blink() print_set_format( blink )
#define print_set_reverse() print_set_format( reverse )
#define print_set_hidden() print_set_format( hidden )
#define print_set_strikethrough() print_set_format( strikethrough )

#define print_unset_bold() print_set_format( no_bold )
#define print_unset_italic() print_set_format( no_italic )
#define print_unset_underline() print_set_format( no_underline )
#define print_unset_blink() print_set_format( no_blink )
#define print_unset_reverse() print_set_format( no_reverse )
#define print_unset_hidden() print_set_format( no_hidden )
#define print_unset_strikethrough() print_set_format( no_strikethrough )

#define print_reset_format() print_set_format( reset )

#define print_clear() system( PICK( OS_WINDOWS, "cls", "clear" ) )

////////////////////////////////
/// mathematics

#define MIN( A, B ) pick( ( A ) < ( B ), ( A ), ( B ) )
#define MIN3( A, B, C ) MIN( A, MIN( B, C ) )
#define MIN4( A, B, C, D ) MIN3( A, B, MIN( C, D ) )
#define MIN5( A, B, C, D, E ) MIN4( A, B, C, MIN( D, E ) )

#define MAX( A, B ) pick( ( A ) > ( B ), ( A ), ( B ) )
#define MAX3( A, B, C ) MAX( A, MAX( B, C ) )
#define MAX4( A, B, C, D ) MAX3( A, B, MAX( C, D ) )
#define MAX5( A, B, C, D, E ) MAX4( A, B, C, MAX( D, E ) )

#define MEDIAN( A, B, C ) pick( ( A ) > ( B ), pick( ( B ) > ( C ), ( B ), MIN( A, C ) ), pick( ( A ) > ( C ), ( A ), MIN( B, C ) ) )
#define MEDIAN4( A, B, C, D ) ( ( ( MIN( MAX( A, B ), MAX( C, D ) ) + MAX( MIN( A, B ), MIN( C, D ) ) ) ) / 2 )
#define MEDIAN4_BITWISE( A, B, C, D ) ( ( ( MIN( MAX( A, B ), MAX( C, D ) ) + MAX( MIN( A, B ), MIN( C, D ) ) ) ) >> 1 )
#define MEDIAN5( A, B, C, D, E ) ( ( A + B + C + D + E - MIN5( A, B, C, D, E ) - MAX5( A, B, C, D, E ) ) / 3 )

#define AVG( A, B ) ( ( ( A ) + ( B ) ) / 2 )
#define AVG_BITWISE( A, B ) ( ( ( A ) + ( B ) ) >> 1 )
#define AVG3( A, B, C ) ( ( ( A ) + ( B ) + ( C ) ) / 3 )
#define AVG4( A, B, C, D ) ( ( ( A ) + ( B ) + ( C ) + ( D ) ) / 4 )
#define AVG4_BITWISE( A, B, C, D ) ( ( ( A ) + ( B ) + ( C ) + ( D ) ) >> 2 )

#define CLAMP( V, MINIMUM, MAXIMUM ) MIN( MAX( ( V ), ( MINIMUM ) ), ( MAXIMUM ) )
#define SATURATE( V ) CLAMP( V, 0, 1 )
#define SQR( V ) ( ( V ) * ( V ) )
#define CUBE( V ) ( ( V ) * ( V ) * ( V ) )
#define ABS( V ) pick( ( V ) < 0, -( V ), V )
#define SIGN( V ) pick( ( V ) >= 0, 1, -1 )
#define SIGN_ZERO( V ) pick( ( V ) > 0, 1, pick( ( V ) < 0, -1, 0 ) )

#define MIX( A, B, AMOUNT ) ( ( A ) + ( AMOUNT ) * ( ( B ) - ( A ) ) )
#define MAP( V, A, B, C, D ) ( ( V ) - ( A ) ) * ( ( D ) - ( C ) ) / ( ( B ) - ( A ) ) + ( C )
#define RANGE( V, LOWER, UPPER ) ( ( V - ( LOWER ) ) / ( ( UPPER ) - ( LOWER ) ) )

////////
// math functions

#define FUNCTION_GROUP_BASE( T, N )\
	embed T##N T##N##_min( T##N const a, T##N const b )\
	{\
		out MIN( a, b );\
	}\
	embed T##N T##N##_min3( T##N const a, T##N const b, T##N const c )\
	{\
		out MIN3( a, b, c );\
	}\
	embed T##N T##N##_min4( T##N const a, T##N const b, T##N const c, T##N const d )\
	{\
		out MIN4( a, b, c, d );\
	}\
	embed T##N T##N##_min5( T##N const a, T##N const b, T##N const c, T##N const d, T##N const e )\
	{\
		out MIN5( a, b, c, d, e );\
	}\
	embed T##N T##N##_max( T##N const a, T##N const b )\
	{\
		out MAX( a, b );\
	}\
	embed T##N T##N##_max3( T##N const a, T##N const b, T##N const c )\
	{\
		out MAX3( a, b, c );\
	}\
	embed T##N T##N##_max4( T##N const a, T##N const b, T##N const c, T##N const d )\
	{\
		out MAX4( a, b, c, d );\
	}\
	embed T##N T##N##_max5( T##N const a, T##N const b, T##N const c, T##N const d, T##N const e )\
	{\
		out MAX5( a, b, c, d, e );\
	}\
	embed T##N T##N##_median( T##N const a, T##N const b, T##N const c )\
	{\
		out MEDIAN( a, b, c );\
	}\
	embed T##N T##N##_median5( T##N const a, T##N const b, T##N const c, T##N const d, T##N const e )\
	{\
		out MEDIAN5( a, b, c, d, e );\
	}\
	embed T##N T##N##_avg3( T##N const a, T##N const b, T##N const c )\
	{\
		out AVG3( a, b, c );\
	}\
	embed T##N T##N##_clamp( T##N const v, T##N const min, T##N const max )\
	{\
		out CLAMP( v, min, max );\
	}\
	embed T##N T##N##_saturate( T##N const v )\
	{\
		out SATURATE( v );\
	}\
	embed T##N T##N##_sqr( T##N const v )\
	{\
		out SQR( v );\
	}\
	embed T##N T##N##_cube( T##N const v )\
	{\
		out CUBE( v );\
	}

#define FUNCTION_GROUP_BASE_NI( T, N )\
	embed T##N T##N##_median4( T##N const a, T##N const b, T##N const c, T##N const d )\
	{\
		out MEDIAN4_BITWISE( a, b, c, d );\
	}\
	embed T##N T##N##_avg( T##N const a, T##N const b )\
	{\
		out AVG_BITWISE( a, b );\
	}\
	embed T##N T##N##_avg4( T##N const a, T##N const b, T##N const c, T##N const d )\
	{\
		out AVG4_BITWISE( a, b, c, d );\
	}\
	embed T##N T##N##_random()\
	{\
		out T##N( rand() );\
	}\
	embed T##N T##N##_random_range( T##N const minimum, T##N const maximum )\
	{\
		out minimum + T##N( ( r4( rand() ) / r4( RAND_MAX ) ) * r4( maximum - minimum + 1 ) );\
	}

#define FUNCTION_GROUP_BASE_IR( T, N )\
	embed T##N T##N##_abs( T##N const v )\
	{\
		out ABS( v );\
	}\
	embed T##N T##N##_sign( T##N const v )\
	{\
		out SIGN( v );\
	}\
	embed T##N T##N##_sign_zero( T##N const v )\
	{\
		out SIGN_ZERO( v );\
	}

#define FUNCTION_GROUP_N( N )\
	FUNCTION_GROUP_BASE( n, N );\
	FUNCTION_GROUP_BASE_NI( n, N )

#define FUNCTION_GROUP_I( N )\
	FUNCTION_GROUP_BASE( i, N );\
	FUNCTION_GROUP_BASE_NI( i, N );\
	FUNCTION_GROUP_BASE_IR( i, N )

#define FUNCTION_GROUP_R( N )\
	FUNCTION_GROUP_BASE( r, N );\
	FUNCTION_GROUP_BASE_IR( r, N );\
	embed r##N r##N##_median4( const r##N a, const r##N b, const r##N c, const r##N d )\
	{\
		out MEDIAN4( a, b, c, d );\
	}\
	embed r##N r##N##_avg( const r##N a, const r##N b )\
	{\
		out AVG( a, b );\
	}\
	embed r##N r##N##_avg4( const r##N a, const r##N b, const r##N c, const r##N d )\
	{\
		out AVG4( a, b, c, d );\
	}\
	embed r##N r##N##_mix( const r##N a, const r##N b, const r##N amount )\
	{\
		out MIX( a, b, amount );\
	}\
	embed r##N r##N##_map( const r##N v, const r##N from_lower, const r##N from_upper, const r##N to_lower, const r##N to_upper )\
	{\
		out MAP( v, from_lower, from_upper, to_lower, to_upper );\
	}\
	embed r##N r##N##_range( const r##N v, const r##N lower, const r##N upper )\
	{\
		out RANGE( v, lower, upper );\
	}\
	embed r##N r##N##_random()\
	{\
		out r##N( rand() );\
	}\
	embed r##N r##N##_random_unit()\
	{\
		out r##N##_random() / r##N( RAND_MAX );\
	}\
	embed r##N r##N##_random_range( const r##N minimum, const r##N maximum )\
	{\
		out minimum + r##N##_random_unit() * ( maximum - minimum );\
	}

FUNCTION_GROUP_N( 1 );
FUNCTION_GROUP_I( 1 );

FUNCTION_GROUP_N( 2 );
FUNCTION_GROUP_I( 2 );

FUNCTION_GROUP_N( 4 );
FUNCTION_GROUP_I( 4 );
FUNCTION_GROUP_R( 4 );
#define r4_trunc truncf
#define r4_floor floorf
#define r4_ceil ceilf
#define r4_round roundf
#define r4_mod fmodf
#define r4_sqrt sqrtf
#define r4_pow powf
#define r4_sincos sincosf
#define r4_sin sinf
#define r4_cos cosf
#define r4_tan tanf
#define r4_asin asinf
#define r4_acos acosf
#define r4_atan atanf
#define r4_atanyx atan2f

FUNCTION_GROUP_N( 8 );
FUNCTION_GROUP_I( 8 );
FUNCTION_GROUP_R( 8 );
#define r8_round round
#define r8_trunc trunc
#define r8_floor floor
#define r8_ceil ceil
#define r8_mod fmod
#define r8_sqrt sqrt
#define r8_pow pow
#define r8_sincos sincos
#define r8_sin sin
#define r8_cos cos
#define r8_tan tan
#define r8_asin asin
#define r8_acos acos
#define r8_atan atan
#define r8_atanyx atan2

#if OS_WINDOWS and COMPILER_TCC
	fn sincosf( r4 const x, r4 const ref sin_x, r4 const ref cos_x )
	{
		val_of( sin_x ) = r4_sin( x );
		val_of( cos_x ) = r4_cos( x );
	}

	fn sincos( r8 const x, r8 const ref sin_x, r8 const ref cos_x )
	{
		val_of( sin_x ) = r8_sin( x );
		val_of( cos_x ) = r8_cos( x );
	}
#endif

////////////////////////////////
/// list

object( list )
{
	n2 type_size;
	n4 count;
	byte ref bytes;
	n4 capacity;
};

embed list _new_list( n2 const type_size, n4 const count, byte ref const bytes, n4 const capacity )
{
	temp list const out_list = new_object( list );
	out_list->type_size = type_size;
	out_list->count = count;
	out_list->bytes = bytes;
	out_list->capacity = pick( capacity <= count, count + 1, capacity );
	out out_list;
}
#define new_list_bytes( TYPE, COUNT, BYTES, CAPACITY ) _new_list( size_of( TYPE ), COUNT, to( byte ref, BYTES ), CAPACITY )
#define new_list( TYPE, CAPACITY... ) new_list_bytes( TYPE, 0, new_ref( TYPE, DEFAULT( 1, CAPACITY ) ), DEFAULT( 1, CAPACITY ) )

delete_object_fn( list )
{
	delete_ref( this->bytes );
	delete_object( this );
}

object_fn( list, grow )
{
	out_if( this->capacity > this->count );

	temp n4 const old_capacity = this->capacity;
	this->capacity = ( ( this->capacity + ( this->count << 1 ) + 1 ) >> 1 ) + 1;
	this->bytes = _ref_resize( this->bytes, this->type_size, old_capacity, this->capacity );
}

object_fn( list, shrink )
{
	temp n4 const old_capacity = this->capacity;
	this->capacity = this->count + 1;
	this->bytes = _ref_resize( this->bytes, this->type_size, old_capacity, this->capacity );
}

object_fn( list, set_count, n4 const count )
{
	this->count = count;
	list_grow( this );
}

#define list_set( LIST, POS, VAL ) ( to( type_of( VAL ) ref, LIST->bytes ) )[ ( POS ) ] = ( VAL )
#define list_get( LIST, TYPE, POS ) ( ( to( TYPE ref, LIST->bytes ) )[ ( POS ) ] )

object_fn( list, clear )
{
	this->count = 0;
	bytes_clear( this->bytes, this->type_size );
}

object_fn( list, move, n4 const position, n4 const count, i4 const move_amount )
{
	temp n4 const sized_position = position * this->type_size;
	bytes_move( this->bytes, sized_position, count * this->type_size, move_amount * this->type_size );
}

#define list_copy_bytes( LIST, POSITION, BYTES, BYTES_COUNT ) bytes_copy( LIST->bytes + ( ( POSITION ) * LIST->type_size ), BYTES, BYTES_COUNT )

#define list_copy( LIST, POSITION, FROM_LIST, FROM_POSITION, FROM_COUNT ) list_copy_bytes( LIST, POSITION, FROM_LIST->bytes + ( ( FROM_POSITION ) * FROM_LIST->type_size ), ( FROM_COUNT ) * FROM_LIST->type_size )

#define list_add( LIST, VAL )\
	START_DEF\
	{\
		list_grow( LIST );\
		list_set( LIST, LIST->count++, VAL );\
	}\
	END_DEF

#define list_insert( LIST, POS, VAL )\
	START_DEF\
	{\
		list_grow( LIST );\
		list_move( LIST, ( POS ), ( LIST->count++ ) - ( POS ), 1 );\
		list_set( LIST, POS, VAL );\
	}\
	END_DEF

object_fn( list, add_bytes_part, byte const ref const bytes, n4 const bytes_position, n4 const count )
{
	temp n4 const old_count = this->count;
	list_set_count( this, this->count + count );
	list_copy_bytes( this, old_count, bytes + bytes_position, count * this->type_size );
}
#define list_add_bytes( LIST, BYTES, COUNT... ) list_add_bytes_part( LIST, BYTES, 0, DEFAULT( bytes_measure( BYTES ), COUNT ) )
#define list_add_list_part( LIST, OTHER_LIST, OTHER_POSITION, OTHER_COUNT ) list_add_bytes_part( LIST, OTHER_LIST->bytes, ( OTHER_POSITION ) * OTHER_LIST->type_size, OTHER_COUNT )
#define list_add_list( LIST, OTHER_LIST ) list_add_list_part( LIST, OTHER_LIST, 0, OTHER_LIST->count )

object_fn( list, insert_bytes_part, n4 const position, byte const ref const bytes, n4 const bytes_position, n4 const count )
{
	temp n4 const old_count = this->count;
	list_set_count( this, this->count + count );
	list_move( this, position, old_count - position, count );
	list_copy_bytes( this, position, bytes + bytes_position, count * this->type_size );
}
#define list_insert_bytes( LIST, POSITION, BYTES, COUNT... ) list_insert_bytes_part( LIST, POSITION, BYTES, 0, DEFAULT( bytes_measure( BYTES ), COUNT ) )
#define list_insert_list_part( LIST, POSITION, OTHER_LIST, OTHER_POSITION, OTHER_COUNT ) list_insert_bytes_part( LIST, POSITION, OTHER_LIST->bytes, ( OTHER_POSITION ) * OTHER_LIST->type_size, OTHER_COUNT )
#define list_insert_list( LIST, POSITION, OTHER_LIST ) list_insert_list_part( LIST, POSITION, OTHER_LIST, 0, OTHER_LIST->count )

object_fn( list, replace_bytes_part, n4 const position, n4 const replace_count, byte const ref const bytes, n4 const bytes_position, n4 const count )
{
	temp n4 const old_count = this->count;
	temp n4 const pos = position + replace_count;
	list_set_count( this, this->count - replace_count + count );
	list_move( this, pos, old_count - pos, i4( this->count ) - old_count );
	list_copy_bytes( this, position, bytes + bytes_position, count * this->type_size );

	if( this->count < old_count )
	{
		bytes_clear( this->bytes + ( this->count * this->type_size ), ( old_count - this->count ) * this->type_size );
	}
}
#define list_replace_bytes( LIST, POSITION, REPLACE_COUNT, BYTES, COUNT... ) list_replace_bytes_part( LIST, POSITION, REPLACE_COUNT, BYTES, 0, DEFAULT( bytes_measure( BYTES ), COUNT ) )
#define list_replace_list_part( LIST, POSITION, REPLACE_COUNT, OTHER_LIST, OTHER_POSITION, OTHER_COUNT ) list_replace_bytes_part( LIST, POSITION, REPLACE_COUNT, OTHER_LIST->bytes, ( OTHER_POSITION ) * OTHER_LIST->type_size, OTHER_COUNT )
#define list_replace_list( LIST, POSITION, REPLACE_COUNT, OTHER_LIST ) list_replace_list_part( LIST, POSITION, REPLACE_COUNT, OTHER_LIST, 0, OTHER_LIST->count )

object_fn( list, delete_part, n4 const position, n4 const delete_count )
{
	temp i4 const old_count = this->count;
	temp i4 const pos = position + delete_count;
	list_move( this, pos, old_count - pos, -i4( delete_count ) );
	list_set_count( this, this->count - delete_count );

	bytes_clear( this->bytes + ( this->count * this->type_size ), delete_count * this->type_size );
}
#define list_delete( LIST, POSITION ) list_delete_part( LIST, POSITION, 1 )

#define list_remove( LIST, TYPE, POSITION )\
	list_get( LIST, TYPE, POSITION );\
	list_delete( LIST, POSITION )

#define list_remove_first( LIST, TYPE ) list_remove( LIST, TYPE, 0 )

#define list_remove_last( LIST, TYPE )\
	list_get( LIST, TYPE, --LIST->count );\
	bytes_clear( LIST->bytes + ( LIST->count * LIST->type_size ), LIST->type_size )

#define list_iter( LIST, VAR_NAME )\
	temp list const _LIST_##VAR_NAME = LIST;\
	iter( VAR_NAME, _LIST_##VAR_NAME->count )

#define list_get_iter( VAR_NAME, TYPE ) list_get( _LIST_##VAR_NAME, TYPE, VAR_NAME )

#define list_iter_inv( LIST, VAR_NAME )\
	temp list const _LIST_##VAR_NAME = LIST;\
	iter_inv( VAR_NAME, _LIST_##VAR_NAME->count )

////////////////////////////////
/// text

type_from( list ) text;

#define new_text_bytes( BYTES, COUNT, CAPACITY... ) new_list_bytes( byte, COUNT, bytes_paste( new_ref( byte, DEFAULT( COUNT + 1, CAPACITY ) ), BYTES ), DEFAULT( 1, CAPACITY ) )
#define new_text( CAPACITY... ) new_list( byte, DEFAULT( 1, CAPACITY ) )
#define delete_text delete_list

#define text_set( TEXT, POS, BYTE ) list_set( TEXT, POS, byte( BYTE ) )
#define text_get( TEXT, POS ) list_get( TEXT, byte, POS )
#define text_clear list_clear
#define text_move list_move
#define text_copy list_copy

#define text_add( TEXT, BYTE ) list_add( TEXT, byte( BYTE ) )
#define text_insert( TEXT, POS, BYTE ) list_insert( TEXT, POS, byte( BYTE ) )

#define text_add_bytes_part list_add_bytes_part
#define text_add_bytes list_add_bytes
#define text_insert_bytes_part list_insert_bytes_part
#define text_insert_bytes list_insert_bytes
#define text_replace_bytes_part list_replace_bytes_part
#define text_replace_bytes list_replace_bytes

#define text_add_text_part list_add_list_part
#define text_add_text list_add_list
#define text_insert_text_part list_insert_list_part
#define text_insert_text list_insert_list
#define text_replace_text_part list_replace_list_part
#define text_replace_text list_replace_list

#define text_delete_part list_delete_part
#define text_delete list_delete

#define text_remove( TEXT, POSITION ) list_remove( TEXT, byte, POSITION )
#define text_remove_first( TEXT ) list_remove_first( TEXT, byte )
#define text_remove_last( TEXT ) list_remove_last( TEXT, byte )

#define text_end( TEXT ) TEXT->bytes[ TEXT->count ] = eof_byte
#define text_newline( TEXT ) text_add( TEXT, newline_byte )

#define print_text( TEXT ) print( TEXT->bytes )

////////////////////////////////
/// OS file

type_from( FILE ref ) os_file_handle;

#define os_file_get_line fgets
#define system_read( COMMAND ) popen( COMMAND, "r" )

////////
// input

embed byte const ref const get_os_input()
{
	perm byte print_input[ KB( 1 ) ];
	os_file_get_line( print_input, size_of_bytes( print_input ), stdin );
	temp n2 const input_size = bytes_measure( print_input );
	out_if( input_size is 0 ) nothing;
	print_input[ input_size - 1 ] = eof_byte;
	out print_input;
}

////////////////////////////////
/// OS path

#define max_path_size 260

#define path( FOLDERS... ) CHAIN(,, separator, FOLDERS )

fn path_up_folder( byte ref const path )
{
	temp byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt '\\' and val_of( p ) isnt '/' );
	if( p > path ) val_of( p ) = eof_byte;
}

embed byte ref const path_get_name( byte ref const path )
{
	temp byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt '\\' and val_of( p ) isnt '/' );
	if( p > path ) ++p;
	out p;
}

embed byte ref const path_get_extension( byte ref const path )
{
	temp byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt '.' );
	if( p > path ) ++p;
	out p;
}

embed byte ref get_exe_path()
{
	perm byte exe_path[ max_path_size ] = "";
	#if OS_LINUX
		temp i8 _s = readlink( "/proc/self/exe", exe_path, max_path_size );
	#elif OS_WINDOWS
		GetModuleFileNameA( nothing, exe_path, max_path_size );
	#endif
	out exe_path;
}

////////////////////////////////
/// OS entries (folders/files)

#define max_entry_size 65

group( entry_type )
{
	entry_unknown,
	entry_folders,
	entry_files,
	entry_any
};

embed n2 get_entries( byte const ref const folder_path, byte entries[][ max_path_size ], n2 const max_entries, entry_type const type, flag const folder_separator )
{
	temp n2 count = 0;
	temp n2 len = bytes_measure( folder_path );
	perm byte path[ max_path_size ];
	bytes_clear( path, max_path_size );
	anon ref handle;
	bytes_copy( path, folder_path, len );

	#if OS_LINUX
		struct dirent ref entry;
		struct stat stat_buf;
		handle = opendir( path );
		if_nothing( handle ) out 0;
		path[ len++ ] = '/';
		while( ( entry = readdir( handle ) ) and count < max_entries )
		{
			next_if( entry->d_name[ 0 ] is '.' );
			temp n2 entry_size = bytes_measure( entry->d_name ) + 1;
			bytes_copy( path + len, entry->d_name, entry_size );

			if( stat( path, ref_of( stat_buf ) ) is 0 )
			{
				temp flag is_dir = flag( S_ISDIR( stat_buf.st_mode ) );
				if( type is entry_any or ( type is entry_folders and is_dir is yes ) or ( type is entry_files and is_dir is no ) )
				{
					bytes_copy( entries[ count ], entry->d_name, entry_size );
					if( is_dir and folder_separator )
					{
						entries[ count ][ entry_size - 1 ] = val_of( separator );
						entries[ count ][ entry_size ] = eof_byte;
					}
					++count;
				}
			}
		}
		closedir( handle );
	#elif OS_WINDOWS
		WIN32_FIND_DATA entry;
		bytes_copy( path + len, "\\*", 3 );
		handle = FindFirstFile( path, ref_of( entry ) );
		if( handle is INVALID_HANDLE_VALUE ) out 0;

		do
		{
			next_if( entry.cFileName[ 0 ] is '.' );
			temp flag is_dir = flag( entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY );
			if( type is entry_any or ( type is entry_folders and is_dir is yes ) or ( type is entry_files and is_dir is no ) )
			{
				temp n2 entry_size = bytes_measure( entry.cFileName ) + 1;
				bytes_copy( entries[ count++ ], entry.cFileName, entry_size );
				if( is_dir and folder_separator )
				{
					entries[ count ][ entry_size - 1 ] = val_of( separator );
					entries[ count ][ entry_size ] = eof_byte;
				}
			}
		}
		while( count < max_entries and FindNextFile( handle, ref_of( entry ) ) );
		FindClose( handle );
	#endif
	out count;
}

#define get_files( PATH, OUT_ENTRIES, MAX_ENTRIES ) get_entries( PATH, OUT_ENTRIES, MAX_ENTRIES, entry_files, no )
#define get_folders( PATH, OUT_ENTRIES, MAX_ENTRIES, FOLDER_SEPARATOR... ) get_entries( PATH, OUT_ENTRIES, MAX_ENTRIES, entry_folders, DEFAULT( yes, FOLDER_SEPARATOR ) )

////////////////////////////////
/// folders

fn create_folder( byte const ref const path )
{
	#if OS_LINUX
		mkdir( path, 0755 );
	#else
		CreateDirectoryA( path, nothing );
	#endif
}

fn delete_folder( byte const ref const path )
{
	#if OS_LINUX
		rmdir( path );
	#else
		RemoveDirectoryA( path );
	#endif
}

embed flag folder_exists( byte const ref const path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISDIR( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and ( attrib & FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

embed flag file_exists( byte const ref const path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISREG( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and not ( attrib & FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

////////////////////////////////
/// files

type( file )
{
	byte path[ max_path_size ];
	n2 path_size;
	os_file_handle handle;
	byte ref mapped_bytes;
	n8 size;
};

embed n8 get_file_size( byte const ref const file_path )
{
	#if OS_LINUX
		struct stat st;
		out pick( stat( file_path, ref_of( st ) ) is 0, to( n8 const, st.st_size ), 0 );
	#elif OS_WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		out pick( GetFileAttributesExA( file_path, GetFileExInfoStandard, ref_of( fad ) ), to( n8 const, ( n8( fad.nFileSizeHigh ) << 32 ) | n8( fad.nFileSizeLow ) ), 0 );
	#endif
}

embed file _open_file_loading( byte const ref const path, n4 const path_size )
{
	file f = { 0 };
	f.size = get_file_size( path );
	if( f.size is 0 )
	{
		out f;
	}

	f.handle = fopen( path, "rb" );
	if_nothing( f.handle )
	{
		out f;
	}

	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );

	out f;
}

embed file _open_file_saving( byte const ref const path, n4 const path_size )
{
	file f = { 0 };
	f.handle = fopen( path, "wb" );
	if_nothing( f.handle )
	{
		out f;
	}

	f.size = 0;
	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );

	out f;
}

#define open_file( PATH, PATH_SIZE... ) _open_file_loading( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )
#define new_file( PATH, PATH_SIZE... ) _open_file_saving( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )

embed file _map_file( byte const ref const path, n4 const path_size )
{
	file f = { 0 };

	f.size = get_file_size( path );
	if( f.size is 0 )
	{
		out f;
	}

	#if OS_LINUX
		temp i4 fd = open( path, O_RDONLY );
		out_if( fd is -1 ) f;

		temp anon ref mapped_bytes = mmap( nothing, f.size, PROT_READ, MAP_PRIVATE, fd, 0 );
		close( fd );
		out_if( mapped_bytes is MAP_FAILED ) f;
		f.mapped_bytes = to( byte ref, mapped_bytes );
	#elif OS_WINDOWS
		temp HANDLE file = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, nothing, OPEN_EXISTING, 0, nothing );
		out_if( file is INVALID_HANDLE_VALUE ) f;

		temp HANDLE mapping = CreateFileMapping( file, nothing, PAGE_READONLY, 0, 0, nothing );
		CloseHandle( file );
		if_nothing( mapping )
		{
			out f;
		}

		f.mapped_bytes = to( byte ref, MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, 0 ) );
		CloseHandle( mapping );
	#endif

	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );

	out f;
}
#define map_file( PATH, PATH_SIZE... ) _map_file( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )

fn file_load( file ref f, byte ref const out_bytes )
{
	if_nothing( f->handle ) out;

	fseek( f->handle, 0, SEEK_SET );
	fread( out_bytes, 1, f->size, f->handle );
}

fn file_save( file ref f, byte const ref const bytes, n8 const size )
{
	if_nothing( f->handle ) out;

	fseek( f->handle, 0, SEEK_SET );
	f->size = size;
	fwrite( bytes, 1, f->size, f->handle );
	fflush( f->handle );
}

fn file_clear( file ref f )
{
	f->handle = nothing;
	bytes_clear( f->path, f->path_size );
	f->path_size = 0;
	f->size = 0;
}

fn file_close( file ref f )
{
	if_something( f->handle )
	{
		fclose( f->handle );
	}

	file_clear( f );
}

fn file_unmap( file ref f )
{
	if_something( f->mapped_bytes )
	{
		#if OS_LINUX
			munmap( f->mapped_bytes, f->size );
		#elif OS_WINDOWS
			UnmapViewOfFile( f->mapped_bytes );
		#endif
	}

	file_clear( f );
}

fn delete_file( const byte ref const path )
{
	remove( path );
}

////////////////////////////////
/// sleep

#if OS_LINUX
	#define sleep(ms) usleep((ms) * 1000)
#elif OS_WINDOWS
	#define sleep(ms) Sleep(ms)
#endif

////////////////////////////////
/// OS threads

type_from( PICK( OS_LINUX, pthread_t, HANDLE ) ) thread_id;

fn_type( anon ref, anon ref ) thread_fn;

type( thread )
{
	thread_id id;
	thread_fn function;
};

embed thread _start_thread( thread_fn function, anon ref ref_param )
{
	thread out_thread;
	out_thread.function = function;
	out_thread.id = 0;
	#if OS_WINDOWS
		out_thread.id = CreateThread( nothing, 0, to( LPTHREAD_START_ROUTINE, out_thread.function ), ref_param, 0, nothing );
	#elif OS_LINUX
		pthread_create( ref_of( out_thread.id ), nothing, out_thread.function, ref_param );
	#endif

	out out_thread;
}
#define start_thread( FN, REF_PARAM ) _start_thread( to( thread_fn, FN ), to( anon ref, REF_PARAM ) )

#if OS_LINUX
	#define wait_for_thread( THREAD ) pthread_join( THREAD.id, nothing )
#elif OS_WINDOWS
	#define wait_for_thread( THREAD ) WaitForSingleObject( THREAD.id, INFINITE )
#endif

type_from( PICK( OS_LINUX, pthread_mutex_t, CRITICAL_SECTION ) ) thread_lock;

#if OS_LINUX
	#define lock_thread( LOCK ) pthread_mutex_lock( ref_of( LOCK ) )
	#define unlock_thread( LOCK ) pthread_mutex_unlock( ref_of( LOCK ) )
	#define thread_add_lock( LOCK ) pthread_mutex_init( ref_of( LOCK ), nothing )
	#define thread_remove_lock( LOCK ) pthread_mutex_destroy( ref_of( LOCK ) )
#elif OS_WINDOWS
	#define lock_thread( LOCK ) EnterCriticalSection( ref_of( LOCK ) )
	#define unlock_thread( LOCK ) LeaveCriticalSection( ref_of( LOCK ) )
	#define thread_add_lock( LOCK ) InitializeCriticalSection( ref_of( LOCK ) )
	#define thread_remove_lock( LOCK ) DeleteCriticalSection( ref_of( LOCK ) )
#endif

////////////////////////////////
/// start

#define _main_fn out_state main( i4 const start_parameters_count, byte const ref const ref const start_parameters )
#define start _main_fn

////////////////////////////////////////////////////////////////
