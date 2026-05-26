////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Hydrogen Language (H)
//
//  author(s):
//  ENDESGA - https://twitter.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/H
//  2026 - CC0 - FOSS forever
//

#pragma once

#pragma clang diagnostic ignored "-Wpragma-pack"
#pragma clang diagnostic ignored "-Waddress-of-packed-member"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DEPENDENCIES
//

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

////////////////////////////////////////////////////////////////
#pragma region - operating system

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_UNKNOWN 0

#if defined( __linux__ )
	#undef OS_LINUX
	#define OS_LINUX 1
	#define OS_NAME "Linux"
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <dirent.h>
	#include <fcntl.h>
	#include <unistd.h>

#elif defined( _WIN32 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
	#define OS_NAME "Windows"
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>

#elif defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
	#define OS_NAME "macOS"

#else
	#undef OS_UNKNOWN
	#define OS_UNKNOWN 1
	#define OS_NAME "unknown"
#endif

#pragma endregion operating system

////////////////////////////////////////////////////////////////
#pragma region - compiler

#define COMPILER_GCC 0
#define COMPILER_TCC 0
#define COMPILER_UNKNOWN 0

#if defined( __TINYC__ )
	#undef COMPILER_TCC
	#define COMPILER_TCC 1
	#define COMPILER_NAME "TCC"

#elif defined( __GNUC__ )
	#undef COMPILER_GCC
	#define COMPILER_GCC 1
	#define COMPILER_NAME "GCC"

#else
	#undef COMPILER_UNKNOWN
	#define COMPILER_UNKNOWN 1
	#define COMPILER_NAME "unknown"
#endif

#pragma endregion compiler

#pragma endregion dependencies

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - MACROS
//

#define _EVAL( INPUTS... ) INPUTS
#define EVAL( INPUTS... ) _EVAL( INPUTS )
#define _JOIN( A, B... ) A##B
#define JOIN( A, B... ) _JOIN( A, B )

#define COMMA ,

#define _AS_BYTES( VALUE ) #VALUE
#define AS_BYTES( VALUE ) _AS_BYTES( VALUE )

#define START_DEF do
#define END_DEF while( 0 )

#define REQUIRE_SEMICOLON START_DEF {} END_DEF

////////////////////////////////////////////////////////////////
#pragma region - input

#define SKIP_INPUT( _, INPUTS... ) INPUTS

#define GET_INPUT0( ... )
#define GET_INPUT1( a, ... ) a
#define GET_INPUT2( a, b, ... ) b
#define GET_INPUT3( a, b, c, ... ) c
#define GET_INPUT4( a, b, c, d, ... ) d
#define GET_INPUT5( a, b, c, d, e, ... ) e
#define GET_INPUT6( a, b, c, d, e, f, ... ) f
#define GET_INPUT7( a, b, c, d, e, f, g, ... ) g
#define GET_INPUT8( a, b, c, d, e, f, g, h, ... ) h
#define GET_INPUT9( a, b, c, d, e, f, g, h, i, ... ) i
#define GET_INPUT10( a, b, c, d, e, f, g, h, i, j, ... ) j
#define GET_INPUT11( a, b, c, d, e, f, g, h, i, j, k, ... ) k
#define GET_INPUT12( a, b, c, d, e, f, g, h, i, j, k, l, ... ) l
#define GET_INPUT13( a, b, c, d, e, f, g, h, i, j, k, l, m, ... ) m
#define GET_INPUT14( a, b, c, d, e, f, g, h, i, j, k, l, m, n, ... ) n
#define GET_INPUT15( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, ... ) o
#define GET_INPUT16( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, ... ) p
#define GET_INPUT17( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, ... ) q

#define _PASTE_IF_INPUTS_EVAL( CODE, INPUTS... ) GET_INPUT2( INPUTS, EVAL CODE )
#define _PASTE_IF_INPUTS( CODE, INPUTS... ) _PASTE_IF_INPUTS_EVAL( CODE, GET_INPUT1 INPUTS( COMMA ) )
#define PASTE_IF_INPUTS( CODE, INPUTS... ) _PASTE_IF_INPUTS( ( CODE ), GET_INPUT1( INPUTS ) )

#define COMMA_IF_INPUTS( INPUTS... ) PASTE_IF_INPUTS( COMMA, INPUTS )

#define _COUNT_INPUTS_EVAL( INPUTS... ) GET_INPUT17( INPUTS, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 )
#define COUNT_INPUTS( INPUTS... ) _COUNT_INPUTS_EVAL( INPUTS COMMA_IF_INPUTS( INPUTS ) 16 )

#pragma endregion input

////////////////////////////////////////////////////////////////
#pragma region - defaults

#define _DEFAULT_EVAL( INPUTS... ) GET_INPUT1( INPUTS )
#define DEFAULT( DEF, INPUTS... ) _DEFAULT_EVAL( INPUTS COMMA_IF_INPUTS( INPUTS ) DEF )
#define _DEFAULTS_0( DEFS, ... )
#define _DEFAULTS_1( DEFS, INPUTS... ) DEFAULT( GET_INPUT1 DEFS, INPUTS )
#define _DEFAULTS_2( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_1( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_3( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_2( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_4( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_3( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_5( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_4( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_6( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_5( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_7( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_6( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_8( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_7( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_9( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_8( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_10( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_9( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_11( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_10( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_12( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_11( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_13( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_12( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_14( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_13( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_15( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_14( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_16( DEFS, INPUTS... ) _DEFAULTS_1( DEFS, INPUTS ) , _DEFAULTS_15( ( SKIP_INPUT DEFS ), SKIP_INPUT( INPUTS ) )
#define _DEFAULTS_MAKE( COUNT, DEFS, INPUTS... ) JOIN( _DEFAULTS_, COUNT ) ( DEFS, INPUTS )
#define DEFAULTS( DEFS, INPUTS... ) _DEFAULTS_MAKE( COUNT_INPUTS DEFS, DEFS, INPUTS )

#pragma endregion defaults

////////////////////////////////////////////////////////////////
#pragma region - chain

#define _CHAIN_0( MODE, L, R, MID, INPUTS... ) INPUTS
#define _CHAIN_1_EMPTY( L, R, MID, INPUT ) L INPUT R
#define _CHAIN_1_PAREN( L, R, MID, INPUT ) ( L INPUT R )
#define _CHAIN_1( MODE, L, R, MID, INPUT ) _CHAIN_1_##MODE( L, R, MID, INPUT )
#define _CHAIN_JOIN( MODE, L, R, MID, INPUT, NEXT ) _CHAIN_1( MODE, L, R, MID, INPUT ) MID NEXT
#define _CHAIN_2( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_1( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_3( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_2( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_4( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_3( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_5( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_4( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_6( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_5( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_7( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_6( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_8( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_7( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_9( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_8( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_10( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_9( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_11( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_10( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_12( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_11( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_13( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_12( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_14( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_13( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_15( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_14( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_16( MODE, L, R, MID, INPUT, INPUTS... ) _CHAIN_JOIN( MODE, L, R, MID, INPUT, _CHAIN_15( MODE, L, R, MID, INPUTS ) )
#define _CHAIN_MAKE( COUNT, MODE, L, R, MID, INPUTS... ) JOIN( _CHAIN_, COUNT ) ( MODE, L, R, MID, INPUTS )

#define CHAIN( L, R, MID, INPUTS... ) _CHAIN_MAKE( COUNT_INPUTS( INPUTS ), EMPTY, L, R, MID, INPUTS )
#define CHAIN_PAREN( L, R, MID, INPUTS... ) _CHAIN_MAKE( COUNT_INPUTS( INPUTS ), PAREN, L, R, MID, INPUTS )

#pragma endregion chain

////////////////////////////////////////////////////////////////
#pragma region - prefix

#define perm static

#if OS_LINUX
	#define cache_align __attribute__( ( aligned( 64 ) ) )
#else
	#define cache_align __declspec( align( 64 ) )
#endif

#pragma endregion prefix

////////////////////////////////////////////////////////////////
#pragma region - type

#define anon void
#define type_from( TYPE... ) typedef TYPE

#define to( TYPE, VAL... ) ( TYPE ) ( VAL )
#define cast( TYPE, VAR... ) val_of( to( TYPE ref, ref_of( VAR ) ) )

#define size_of( TYPE... ) sizeof( TYPE )
#define size_of_bytes( BYTES ) ( size_of( BYTES ) - 1 )
#define size_of_array( ARRAY ) ( size_of( ARRAY ) / size_of( ( ARRAY )[ 0 ] ) )

#define type_of( VAR... ) typeof( VAR )
#define type_of_ref( REF... ) type_of( val_of( to( type_of( REF ), nothing ) ) )

////////////////
#pragma region | - reference

#define ref *

#define ref_of( VAR... ) ( & ( VAR ) )
#define val_of( REF... ) ( * ( REF ) )

#pragma endregion

#pragma endregion type

////////////////////////////////////////////////////////////////
#pragma region - logic

#define not !
#define and &&
#define or ||
#define xor ^
#define mod %
#define is ==
#define isnt !=
#define is_even mod 2 is 0
#define is_odd mod 2 isnt 0

#define pick( IF_YES, THEN_THIS, ELSE_THIS... ) ( ( IF_YES ) ? ( THEN_THIS ) : ( ELSE_THIS ) )
#define PICK_0( THEN_THIS, ELSE_THIS... ) ELSE_THIS
#define PICK_1( THEN_THIS, ELSE_THIS... ) THEN_THIS
#define PICK( IF_1, THEN_THIS, ELSE_THIS... ) JOIN( PICK_, IF_1 ) ( THEN_THIS, ELSE_THIS )
#define OS_PICK( LINUX, WINDOWS ) PICK( OS_LINUX, LINUX, WINDOWS )

#define if_nothing( INPUT... ) if( INPUT is nothing )
#define if_something( INPUT... ) if( INPUT isnt nothing )

#define any( INPUTS... ) ( CHAIN_PAREN(,, or, INPUTS ) )
#define all( INPUTS... ) ( CHAIN_PAREN(,, and, INPUTS ) )
#define none( INPUTS... ) ( not any( INPUTS ) )
#define not_all( INPUTS... ) ( not all( INPUTS ) )

#define if_any( INPUTS... ) if any( INPUTS )
#define if_all( INPUTS... ) if all( INPUTS )
#define if_none( INPUTS... ) if none( INPUTS )
#define if_not_all( INPUTS... ) if not_all( INPUTS )

#pragma endregion logic

////////////////////////////////////////////////////////////////
#pragma region - function

#define embed perm
#define fn embed anon
#define out return

#define fn_ref( OUTPUT, NAME, INPUT_TYPES... ) OUTPUT( ref NAME ) ( INPUT_TYPES )
#define type_fn( OUTPUT, INPUT_TYPES... ) type_from( type_of( fn_ref( DEFAULT( anon, OUTPUT ),, INPUT_TYPES ) ) )

#define call( FN, INPUTS... ) if_something( FN ) FN( INPUTS )

#pragma endregion function

////////////////////////////////////////////////////////////////
#pragma region - value

////////////////
#pragma region | - bits

#if COMPILER_TCC
	#define n_to_bits( N ) pick( ( N ) <= 2, 1, pick( ( N ) <= 4, 2, pick( ( N ) <= 8, 3, pick( ( N ) <= 16, 4, pick( ( N ) <= 32, 5, pick( ( N ) <= 64, 6, pick( ( N ) <= 128, 7, pick( ( N ) <= 256, 8, pick( ( N ) <= 512, 9, pick( ( N ) <= 1024, 10, pick( ( N ) <= 2048, 11, pick( ( N ) <= 4096, 12, pick( ( N ) <= 8192, 13, pick( ( N ) <= 16384, 14, pick( ( N ) <= 32768, 15, pick( ( N ) <= 65536, 16, 32 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )
#else
	#define n_to_bits( N ) pick( ( N ) <= 2, 1, ( 32 - __builtin_clz( ( N ) - 1 ) ) )
#endif

#define bits( N ) : n_to_bits( N )

#define bits_flag : 1

#pragma endregion

#pragma endregion value

////////////////////////////////////////////////////////////////
#pragma region - declare

#define packed __attribute__( ( packed ) )
#define variant struct

#define type( NAME )\
	type_from( variant NAME ) NAME;\
	variant packed NAME

#define make( TYPE, ELEMENT_VALUES... ) ( ( TYPE ) { ELEMENT_VALUES } )

#define wipe( VAL ) VAL = make( type_of( VAL ), 0 )

#define fusion( NAME )\
	type_from( union NAME ) NAME;\
	union packed NAME

#define group( NAME, TYPE... ) PASTE_IF_INPUTS( type_from( DEFAULT( n1, TYPE ) ) NAME;, NAME ) enum packed NAME

#define global perm variant packed

#pragma endregion declare

////////////////////////////////////////////////////////////////
#pragma region - flow

////////////////
#pragma region | - loop

#define loop for( ;; )
#define next continue
#define skip break
#define jump goto
#define until( INPUTS... ) while( not( INPUTS ) )

#pragma endregion

////////////////
#pragma region | - with

#define with switch
#define when( INPUTS... ) CHAIN( case, :,, INPUTS )
#define other default:

#pragma endregion

////////////////
#pragma region | - range

#define _range( POS_NAME, FROM, TO, STEP, SYMBOL_COMPARE, SYMBOL_STEP ) for( i8 POS_NAME = i8( FROM ); POS_NAME SYMBOL_COMPARE i8( TO ); POS_NAME SYMBOL_STEP i8( STEP ) )

#define range_step( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, <=, += )
#define range_step_inv( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, >=, -= )

#define range( POS_NAME, FROM, TO ) range_step( POS_NAME, FROM, TO, 1 )
#define range_inv( POS_NAME, FROM, TO ) range_step_inv( POS_NAME, FROM, TO, 1 )

#define range_grid( X_NAME, Y_NAME, X_FROM, X_TO, Y_FROM, Y_TO ) range( Y_NAME, Y_FROM, Y_TO ) range( X_NAME, X_FROM, X_TO )

#pragma endregion

////////////////
#pragma region | - iterate

#define iter_step( POS_NAME, SIZE, STEP ) _range( POS_NAME, 0, SIZE, STEP, <, += )
#define iter_step_inv( POS_NAME, SIZE, STEP ) _range( POS_NAME, SIZE, 0, STEP, >, -= )

#define iter( POS_NAME, SIZE ) _range( POS_NAME, 0, SIZE, 1, <, += )
#define iter_inv( POS_NAME, SIZE ) _range( POS_NAME, SIZE - 1, 0, 1, >=, -= )

#define iter_grid( X_NAME, Y_NAME, WIDTH, HEIGHT ) iter( Y_NAME, HEIGHT ) iter( X_NAME, WIDTH )

#define _repeat( N_TIMES, COUNTER ) iter( JOIN( _REP_, COUNTER ), N_TIMES )
#define repeat( N_TIMES ) _repeat( N_TIMES, __COUNTER__ )

#pragma endregion

////////////////
#pragma region | - conditional

#define _once( _ONCE_ )\
	perm flag _ONCE_ = yes;\
	if( _ONCE_ and( _ONCE_ = no, yes ) )
#define once _once( JOIN( _ONCE_, __COUNTER__ ) )

#define while_any( INPUTS... ) while any( INPUTS )
#define while_all( INPUTS... ) while all( INPUTS )
#define while_none( INPUTS... ) while none( INPUTS )
#define while_not_all( INPUTS... ) while not_all( INPUTS )

#define skip_if( INPUT... ) if( INPUT ) skip
#define skip_if_nothing( INPUT... ) if_nothing( INPUT ) skip
#define skip_if_something( INPUT... ) if_something( INPUT ) skip
#define skip_if_any( INPUTS... ) if_any( INPUTS ) skip
#define skip_if_all( INPUTS... ) if_all( INPUTS ) skip
#define skip_if_none( INPUTS... ) if_none( INPUTS ) skip
#define skip_if_not_all( INPUTS... ) if_not_all( INPUTS ) skip

#define jump_if( INPUT... ) if( INPUT ) jump
#define jump_if_nothing( INPUT... ) if_nothing( INPUT ) jump
#define jump_if_something( INPUT... ) if_something( INPUT ) jump
#define jump_if_any( INPUTS... ) if_any( INPUTS ) jump
#define jump_if_all( INPUTS... ) if_all( INPUTS ) jump
#define jump_if_none( INPUTS... ) if_none( INPUTS ) jump
#define jump_if_not_all( INPUTS... ) if_not_all( INPUTS ) jump

#define next_if( INPUT... ) if( INPUT ) next
#define next_if_nothing( INPUT... ) if_nothing( INPUT ) next
#define next_if_something( INPUT... ) if_something( INPUT ) next
#define next_if_any( INPUTS... ) if_any( INPUTS ) next
#define next_if_all( INPUTS... ) if_all( INPUTS ) next
#define next_if_none( INPUTS... ) if_none( INPUTS ) next
#define next_if_not_all( INPUTS... ) if_not_all( INPUTS ) next

#define out_if( INPUT... ) if( INPUT ) out
#define out_if_nothing( INPUT... ) if_nothing( INPUT ) out
#define out_if_something( INPUT... ) if_something( INPUT ) out
#define out_if_any( INPUTS... ) if_any( INPUTS ) out
#define out_if_all( INPUTS... ) if_all( INPUTS ) out
#define out_if_none( INPUTS... ) if_none( INPUTS ) out
#define out_if_not_all( INPUTS... ) if_not_all( INPUTS ) out

#pragma endregion

#pragma endregion flow

////////////////////////////////////////////////////////////////
#pragma region - inputs

#define inputs_list va_list
#define inputs_init( INPUT_LIST_REF, BEFORE_ELLIPSIS ) va_start( INPUT_LIST_REF, BEFORE_ELLIPSIS )
#define inputs_end( INPUT_LIST_REF ) va_end( INPUT_LIST_REF )
#define inputs_copy( FROM, TO ) va_copy( TO, FROM )

#define _inputs_next_byte int
#define _inputs_next_n1 unsigned int
#define _inputs_next_i1 signed int
#define _inputs_next_n2 unsigned int
#define _inputs_next_i2 signed int
#define _inputs_next_n4 unsigned int
#define _inputs_next_i4 signed int
#define _inputs_next_r4 double
#define _inputs_next_n8 unsigned long long
#define _inputs_next_i8 signed long long
#define _inputs_next_r8 double
#define _inputs_next_ref long ref
#define inputs_next( INPUTS, TYPE ) va_arg( INPUTS, _inputs_next_##TYPE )

#pragma endregion inputs

////////////////////////////////////////////////////////////////
#pragma region - bytes

#define is_letter( BYTE ) ( ( ( n4( BYTE ) | 0x20 ) - 'a' ) < 26 )
#define is_number( BYTE ) ( ( n4( BYTE ) - '0' ) < 10 )

#define to_upper_case( BYTE ) ( ( BYTE ) ^ ( ( n1( ( BYTE ) - 'a' ) < 26 ) << 5 ) )
#define to_lower_case( BYTE ) ( ( BYTE ) ^ ( ( n1( ( BYTE ) - 'A' ) < 26 ) << 5 ) )

#define KB( KILOBYTES ) ( ( KILOBYTES ) * 1000 )
#define MB( MEGABYTES ) ( ( MEGABYTES ) * 1000000 )
#define GB( GIGABYTES ) ( ( GIGABYTES ) * 1000000000 )

#define KiB( KIBIBYTES ) ( ( KIBIBYTES ) << 10 )
#define MiB( MEBIBYTES ) ( ( MEBIBYTES ) << 20 )
#define GiB( GIBIBYTES ) ( ( GIBIBYTES ) << 30 )

#pragma endregion bytes

////////////////////////////////////////////////////////////////
#pragma region - mathematics

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

#pragma endregion mathematics

#pragma endregion macros

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - CONSTANTS
//

#define H_NAME "H"

////////////////////////////////////////////////////////////////
#pragma region - version

#define H_VERSION_MAJOR 0
#define H_VERSION_MINOR 1
#define H_VERSION_PATCH 0
#define H_VERSION_COMMIT 0
#define H_VERSION AS_BYTES( H_VERSION_MAJOR ) "." AS_BYTES( H_VERSION_MINOR ) "." AS_BYTES( H_VERSION_PATCH ) "-" AS_BYTES( H_VERSION_COMMIT )

#pragma endregion version

#pragma endregion defaults

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DECLARATIONS
//

////////////////////////////////////////////////////////////////
#pragma region - flag

type_from( _Bool ) flag;
#define flag( INPUTS... ) to( flag, !! ( INPUTS ) )
#define yes 1
#define no 0
#define flip( FLAG ) FLAG ^= 1

#pragma endregion flag

////////////////////////////////////////////////////////////////
#pragma region - byte

type_from( char ) byte;
#define byte( VAL ) to( byte, VAL )

#pragma endregion byte

////////////////////////////////////////////////////////////////
#pragma region - nir

// natural 1/2/4/8, integer 1/2/4/8, rational 4/8

// 1 byte
type_from( uint8_t ) n1;
#define n1( VAL ) to( n1, VAL )
#define n1_min_val 0
#define n1_max_val UINT8_MAX
//
type_from( int8_t ) i1;
#define i1( VAL ) to( i1, VAL )
#define i1_min_val INT8_MIN
#define i1_max_val INT8_MAX

// 2 bytes
type_from( uint16_t ) n2;
#define n2( VAL ) to( n2, VAL )
#define n2_min_val 0
#define n2_max_val UINT16_MAX
//
type_from( int16_t ) i2;
#define i2( VAL ) to( i2, VAL )
#define i2_min_val INT16_MIN
#define i2_max_val INT16_MAX

// 4 bytes
type_from( uint32_t ) n4;
#define n4( VAL ) to( n4, VAL )
#define n4_min_val 0
#define n4_max_val UINT32_MAX
//
type_from( int32_t ) i4;
#define i4( VAL ) to( i4, VAL )
#define i4_min_val INT32_MIN
#define i4_max_val INT32_MAX
//
type_from( float ) r4;
#define r4( VAL ) to( r4, VAL )

// 8 bytes
type_from( uint64_t ) n8;
#define n8( VAL ) to( n8, VAL )
#define n8_min_val 0
#define n8_max_val UINT64_MAX
//
type_from( int64_t ) i8;
#define i8( VAL ) to( i8, VAL )
#define i8_min_val INT64_MIN
#define i8_max_val INT64_MAX
//
type_from( double ) r8;
#define r8( VAL ) to( r8, VAL )

#pragma endregion nir

////////////////////////////////////////////////////////////////
#pragma region - literal

#define nothing to( anon ref, 0 )

type_from( i4 ) out_state;
#define success 0
#define failure 1
#define warning 2

////////////////
#pragma region | - byte

#define newline "\n"
#define newline_byte '\n'

#define separator OS_PICK( "/", "\\" )
#define separator_byte OS_PICK( '/', '\\' )

#define tab "\t"
#define tab_byte '\t'

#define eof "\0"
#define eof_byte '\0'

#pragma endregion

#pragma endregion literal

////////////////////////////////////////////////////////////////
#pragma region - os

#define path_max_size 260

type_from( FILE ref ) os_handle;
#define os_handle_get_line fgets

group( entry_type )
{
	entry_unknown,
	entry_folders,
	entry_files,
	entry_any
};

type( os_file )
{
	byte path[ path_max_size ];
	n2 path_size;
	os_handle handle;
	byte const ref mapped_bytes;
	n8 size;
};

#pragma endregion os

#pragma endregion declarations

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DEFINITIONS
//

////////////////////////////////////////////////////////////////
#pragma region - bytes

////////////////////////////////
#pragma region | bytes / hidden

////////////////
#pragma region | - common

#define _BYTES_ADD_BUFFER( MAX_BYTES )\
	byte _buffer[ MAX_BYTES ];\
	byte ref _buffer_end = _buffer + MAX_BYTES

#define _BYTES_ADD_NEGATIVE( TO_REF, VAL )\
	if( VAL < 0 )\
	{\
		VAL = -VAL;\
		bytes_set_move( TO_REF, '-' );\
	}

#define _BYTES_DECL_move( TO_REF )
#define _BYTES_DECL( TO_REF ) byte ref _to_ref = ( TO_REF );

#define _BYTES_REF_move( TO_REF ) TO_REF
#define _BYTES_REF( TO_REF ) _to_ref

#pragma endregion

////////////////
#pragma region | - natural

#define _BYTES_ADD_N( TO_REF, VAL )\
	START_DEF\
	{\
		n1 _count = 0;\
		do\
		{\
			val_of( --_buffer_end ) = ( VAL mod 10 ) + '0';\
			VAL /= 10;\
			++_count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, _buffer_end, _count );\
	}\
	END_DEF

#define _GEN_N_TO_BYTES( MOVE, TYPE_BYTES, MAX_BYTES, VAL, TO_REF )\
	START_DEF\
	{\
		_BYTES_DECL##MOVE( TO_REF ) n##TYPE_BYTES _val = ( VAL );\
		_BYTES_ADD_BUFFER( MAX_BYTES );\
		_BYTES_ADD_N( _BYTES_REF##MOVE( TO_REF ), _val );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - integer

#define _BYTES_ADD_I( TO_REF, VAL )\
	START_DEF\
	{\
		_BYTES_ADD_NEGATIVE( TO_REF, VAL );\
		_BYTES_ADD_N( TO_REF, VAL );\
	}\
	END_DEF

#define _GEN_I_TO_BYTES( MOVE, TYPE_BYTES, MAX_BYTES, VAL, TO_REF )\
	START_DEF\
	{\
		_BYTES_DECL##MOVE( TO_REF ) i##TYPE_BYTES _val = ( VAL );\
		_BYTES_ADD_BUFFER( MAX_BYTES );\
		_BYTES_ADD_I( _BYTES_REF##MOVE( TO_REF ), _val );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - rational

#define _BYTES_ADD_R( TO_REF, VAL, N )\
	START_DEF\
	{\
		i##N _whole = to( i##N, VAL );\
		r##N _fract = VAL - _whole;\
		_BYTES_ADD_N( TO_REF, _whole );\
		bytes_set_move( TO_REF, '.' );\
		repeat( N )\
		{\
			_fract *= 10;\
			n1 const _digit = n1( _fract );\
			bytes_set_move( TO_REF, '0' + _digit );\
			_fract -= _digit;\
		}\
	}\
	END_DEF

#define _GEN_R_TO_BYTES( MOVE, TYPE_BYTES, MAX_BYTES, VAL, TO_REF )\
	START_DEF\
	{\
		_BYTES_DECL##MOVE( TO_REF ) r##TYPE_BYTES _val = ( VAL );\
		_BYTES_ADD_BUFFER( MAX_BYTES );\
		_BYTES_ADD_NEGATIVE( _BYTES_REF##MOVE( TO_REF ), _val );\
		_BYTES_ADD_R( _BYTES_REF##MOVE( TO_REF ), _val, TYPE_BYTES );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - octal

#define _BYTES_ADD_OCTAL( TO_REF, VAL )\
	START_DEF\
	{\
		n1 _count = 0;\
		do\
		{\
			val_of( --_buffer_end ) = ( VAL & 7 ) + '0';\
			VAL >>= 3;\
			++_count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, _buffer_end, _count );\
	}\
	END_DEF

#define _GEN_OCTAL_TO_BYTES( MOVE, TYPE_BYTES, MAX_BYTES, VAL, TO_REF )\
	START_DEF\
	{\
		_BYTES_DECL##MOVE( TO_REF ) n##TYPE_BYTES _val = ( VAL );\
		_BYTES_ADD_BUFFER( MAX_BYTES );\
		_BYTES_ADD_OCTAL( _BYTES_REF##MOVE( TO_REF ), _val );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - hexadecimal

#define _BYTES_ADD_HEX( TO_REF, VAL )\
	START_DEF\
	{\
		n1 count = 0;\
		do\
		{\
			val_of( --_buffer_end ) = "0123456789ABCDEF"[ VAL & 0xF ];\
			VAL >>= 4;\
			++count;\
		}\
		while( VAL > 0 );\
		bytes_copy_move( TO_REF, _buffer_end, count );\
	}\
	END_DEF

#define _GEN_HEX_TO_BYTES( MOVE, TYPE_BYTES, MAX_BYTES, VAL, TO_REF )\
	START_DEF\
	{\
		_BYTES_DECL##MOVE( TO_REF ) n##TYPE_BYTES _val = ( VAL );\
		_BYTES_ADD_BUFFER( MAX_BYTES );\
		_BYTES_ADD_HEX( _BYTES_REF##MOVE( TO_REF ), _val );\
	}\
	END_DEF

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | bytes / visible

#define bytes_measure( REF ) strlen( REF )
#define bytes_copy( TO_REF, FROM_REF, FROM_SIZE ) memcpy( TO_REF, FROM_REF, FROM_SIZE )
#define bytes_copy_until( TO_REF, FROM_REF, CHAR, MAX_SIZE ) memccpy( TO_REF, FROM_REF, CHAR, MAX_SIZE )
#define bytes_copy_until_any( TO_REF, FROM_REF, DELIMS ) memcpy( TO_REF, FROM_REF, strcspn( FROM_REF, DELIMS ) )
#define bytes_paste( TO_REF, FROM_REF, SIZE... ) strncpy( TO_REF, FROM_REF, DEFAULT( bytes_measure( FROM_REF ) + 1, SIZE ) )
#define bytes_move( REF, POSITION, SIZE, MOVE_AMOUNT ) memmove( ( REF ) + ( POSITION ) + ( MOVE_AMOUNT ), ( REF ) + ( POSITION ), ( SIZE ) )
#define bytes_fill( REF, VAL, SIZE ) memset( REF, VAL, SIZE )
#define bytes_clear( REF, SIZE ) bytes_fill( REF, 0, SIZE )
#define bytes_compare( A, B, AMOUNT... ) memcmp( A, B, DEFAULT( bytes_measure( B ), AMOUNT ) )
#define bytes_match( A, B, AMOUNT... ) ( bytes_compare( A, B, AMOUNT ) is 0 )
#define bytes_find( BYTES, BYTE, MAX_SIZE ) memchr( BYTES, BYTE, MAX_SIZE )
#define bytes_end( BYTES ) val_of( BYTES ) = eof_byte

#if OS_LINUX
	#define bytes_find_bytes( BYTES, BYTES_SIZE, TARGET, TARGET_SIZE ) memmem( BYTES, BYTES_SIZE, TARGET, TARGET_SIZE )
#elif OS_WINDOWS
	embed byte ref const bytes_find_bytes( byte ref const bytes, n4 const bytes_size, byte ref const bytes_find, n4 const bytes_find_size )
	{
		out_if( bytes_find_size is 0 ) bytes;
		out_if( bytes_size < bytes_find_size ) nothing;

		byte ref bytes_ref = bytes;
		byte ref bytes_find_ref = bytes_find;
		n4 const delta = ( bytes_size - bytes_find_size ) + 1;
		iter( byte_index, delta )
		{
			if( bytes_ref[ byte_index ] is bytes_find_ref[ 0 ] and bytes_match( ref_of( bytes_ref[ byte_index ] ), bytes_find_ref, bytes_find_size ) )
			{
				out ref_of( bytes_ref[ byte_index ] );
			}
		}
		out nothing;
	}
	#define bytes_find_bytes( BYTES, BYTES_SIZE, TARGET, TARGET_SIZE... ) bytes_find_bytes( BYTES, BYTES_SIZE, TARGET, DEFAULT( bytes_measure( TARGET ), TARGET_SIZE ) )
#endif

////////////////
#pragma region | - move

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
		byte const ref const _FROM_REF = FROM_REF;\
		n2 const _PASTE_SIZE = bytes_measure( _FROM_REF );\
		bytes_paste( TO_REF, _FROM_REF, _PASTE_SIZE + 1 );\
		TO_REF += _PASTE_SIZE;\
	}\
	END_DEF

#define bytes_set_move( TO_REF, BYTE ) val_of( TO_REF++ ) = BYTE

#define bytes_newline_move( TO_REF ) bytes_set_move( TO_REF, newline_byte )
#define bytes_separator_move( TO_REF ) bytes_set_move( TO_REF, separator_byte )

#pragma endregion

////////////////
#pragma region | - natural

#define n1_to_bytes( VAL, TO_REF ) _GEN_N_TO_BYTES(, 1, 3, VAL, TO_REF )
#define n1_to_bytes_move( VAL, TO_REF ) _GEN_N_TO_BYTES( _move, 1, 3, VAL, TO_REF )
#define n2_to_bytes( VAL, TO_REF ) _GEN_N_TO_BYTES(, 2, 5, VAL, TO_REF )
#define n2_to_bytes_move( VAL, TO_REF ) _GEN_N_TO_BYTES( _move, 2, 5, VAL, TO_REF )
#define n4_to_bytes( VAL, TO_REF ) _GEN_N_TO_BYTES(, 4, 10, VAL, TO_REF )
#define n4_to_bytes_move( VAL, TO_REF ) _GEN_N_TO_BYTES( _move, 4, 10, VAL, TO_REF )
#define n8_to_bytes( VAL, TO_REF ) _GEN_N_TO_BYTES(, 8, 20, VAL, TO_REF )
#define n8_to_bytes_move( VAL, TO_REF ) _GEN_N_TO_BYTES( _move, 8, 20, VAL, TO_REF )

#pragma endregion

////////////////
#pragma region | - integer

#define i1_to_bytes( VAL, TO_REF ) _GEN_I_TO_BYTES(, 1, 4, VAL, TO_REF )
#define i1_to_bytes_move( VAL, TO_REF ) _GEN_I_TO_BYTES( _move, 1, 4, VAL, TO_REF )
#define i2_to_bytes( VAL, TO_REF ) _GEN_I_TO_BYTES(, 2, 6, VAL, TO_REF )
#define i2_to_bytes_move( VAL, TO_REF ) _GEN_I_TO_BYTES( _move, 2, 6, VAL, TO_REF )
#define i4_to_bytes( VAL, TO_REF ) _GEN_I_TO_BYTES(, 4, 11, VAL, TO_REF )
#define i4_to_bytes_move( VAL, TO_REF ) _GEN_I_TO_BYTES( _move, 4, 11, VAL, TO_REF )
#define i8_to_bytes( VAL, TO_REF ) _GEN_I_TO_BYTES(, 8, 21, VAL, TO_REF )
#define i8_to_bytes_move( VAL, TO_REF ) _GEN_I_TO_BYTES( _move, 8, 21, VAL, TO_REF )

#pragma endregion

////////////////
#pragma region | - rational

#define r4_to_bytes( VAL, TO_REF ) _GEN_R_TO_BYTES(, 4, 32, VAL, TO_REF )
#define r4_to_bytes_move( VAL, TO_REF ) _GEN_R_TO_BYTES( _move, 4, 32, VAL, TO_REF )
#define r8_to_bytes( VAL, TO_REF ) _GEN_R_TO_BYTES(, 8, 64, VAL, TO_REF )
#define r8_to_bytes_move( VAL, TO_REF ) _GEN_R_TO_BYTES( _move, 8, 64, VAL, TO_REF )

#pragma endregion

////////////////
#pragma region | - octal

#define octal_n1_to_bytes( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES(, 1, 3, VAL, TO_REF )
#define octal_n1_to_bytes_move( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES( _move, 1, 3, VAL, TO_REF )
#define octal_n2_to_bytes( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES(, 2, 6, VAL, TO_REF )
#define octal_n2_to_bytes_move( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES( _move, 2, 6, VAL, TO_REF )
#define octal_n4_to_bytes( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES(, 4, 11, VAL, TO_REF )
#define octal_n4_to_bytes_move( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES( _move, 4, 11, VAL, TO_REF )
#define octal_n8_to_bytes( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES(, 8, 22, VAL, TO_REF )
#define octal_n8_to_bytes_move( VAL, TO_REF ) _GEN_OCTAL_TO_BYTES( _move, 8, 22, VAL, TO_REF )

#pragma endregion

////////////////
#pragma region | - hexadecimal

#define hex_n1_to_bytes( VAL, TO_REF ) _GEN_HEX_TO_BYTES(, 1, 2, VAL, TO_REF )
#define hex_n1_to_bytes_move( VAL, TO_REF ) _GEN_HEX_TO_BYTES( _move, 1, 2, VAL, TO_REF )
#define hex_n2_to_bytes( VAL, TO_REF ) _GEN_HEX_TO_BYTES(, 2, 4, VAL, TO_REF )
#define hex_n2_to_bytes_move( VAL, TO_REF ) _GEN_HEX_TO_BYTES( _move, 2, 4, VAL, TO_REF )
#define hex_n4_to_bytes( VAL, TO_REF ) _GEN_HEX_TO_BYTES(, 4, 8, VAL, TO_REF )
#define hex_n4_to_bytes_move( VAL, TO_REF ) _GEN_HEX_TO_BYTES( _move, 4, 8, VAL, TO_REF )
#define hex_n8_to_bytes( VAL, TO_REF ) _GEN_HEX_TO_BYTES(, 8, 16, VAL, TO_REF )
#define hex_n8_to_bytes_move( VAL, TO_REF ) _GEN_HEX_TO_BYTES( _move, 8, 16, VAL, TO_REF )

#pragma endregion

#pragma endregion visible

#pragma endregion bytes

////////////////////////////////////////////////////////////////
#pragma region - os

////////////////////////////////
#pragma region | os / hidden

////////////////
#pragma region | - ref

#define _ALLOC_PAGE_MASK 4095
#define _ALLOC_HEADER size_of( n8 )
#define _alloc_page_round( SIZE ) ( ( ( SIZE ) + _ALLOC_PAGE_MASK ) & ~ _ALLOC_PAGE_MASK )
#define _alloc_base( REF ) ( to( n1 ref, REF ) - _ALLOC_HEADER )
#define _alloc_total( REF ) val_of( to( n8 ref, _alloc_base( REF ) ) )

embed anon ref _alloc( n8 const size )
{
	n8 const total = _alloc_page_round( size + _ALLOC_HEADER );
	#if OS_LINUX
		anon ref const alloc = mmap( nothing, total, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
		out_if( alloc is MAP_FAILED ) nothing;
	#elif OS_WINDOWS
		anon ref const alloc = VirtualAlloc( nothing, total, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
		out_if( alloc is nothing ) nothing;
	#endif
	val_of( to( n8 ref, alloc ) ) = total;
	out to( anon ref, to( n1 ref, alloc ) + _ALLOC_HEADER );
}

fn _free( anon ref const anon_ref )
{
	#if OS_LINUX
		munmap( _alloc_base( anon_ref ), _alloc_total( anon_ref ) );
	#elif OS_WINDOWS
		VirtualFree( _alloc_base( anon_ref ), 0, MEM_RELEASE );
	#endif
}

embed anon ref const _ref_resize( anon ref const anon_ref, n8 const new_size, flag const preserve )
{
	out_if( new_size > n8_max_val - _ALLOC_HEADER - _ALLOC_PAGE_MASK ) nothing;
	out_if( anon_ref is nothing ) _alloc( new_size );

	n8 const old_total = _alloc_total( anon_ref );
	n8 const new_total = _alloc_page_round( new_size + _ALLOC_HEADER );
	out_if( new_total is old_total ) anon_ref;

	#if OS_LINUX
		if( preserve is yes )
		{
			anon ref const new_alloc = mremap( _alloc_base( anon_ref ), old_total, new_total, MREMAP_MAYMOVE );
			out_if( new_alloc is MAP_FAILED ) nothing;
			val_of( to( n8 ref, new_alloc ) ) = new_total;
			out to( anon ref, to( n1 ref, new_alloc ) + _ALLOC_HEADER );
		}
	#endif
	anon ref const new_alloc = _alloc( new_size );
	out_if( new_alloc is nothing ) nothing;

	#if OS_WINDOWS
		if( preserve is yes )
		{
			n8 const old_size = old_total - _ALLOC_HEADER;
			bytes_copy( new_alloc, anon_ref, pick( new_size < old_size, new_size, old_size ) );
		}
	#endif
	_free( anon_ref );
	out new_alloc;
}

#pragma endregion

////////////////
#pragma region | - file

embed n8 _os_file_size( byte const ref const file_path )
{
	#if OS_LINUX
		struct stat st;
		out pick( stat( file_path, ref_of( st ) ) is 0, to( n8 const, st.st_size ), 0 );
	#elif OS_WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		out pick( GetFileAttributesExA( file_path, GetFileExInfoStandard, ref_of( fad ) ), to( n8 const, ( n8( fad.nFileSizeHigh ) << 32 ) | n8( fad.nFileSizeLow ) ), 0 );
	#endif
}

embed os_file _os_file_saving( byte const ref const path, n4 const path_size )
{
	os_file f = { 0 };
	f.handle = fopen( path, "wb" );
	out_if_nothing( f.handle ) f;
	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );
	out f;
}

embed os_file _os_file_loading( byte const ref const path, n4 const path_size )
{
	os_file f = { 0 };
	f.size = _os_file_size( path );
	if( f.size is 0 ) out f;
	f.handle = fopen( path, "rb" );
	out_if_nothing( f.handle ) f;
	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );
	out f;
}

embed os_file _os_map_file( byte const ref const path, n4 const path_size )
{
	os_file f = { 0 };
	f.size = _os_file_size( path );
	if( f.size is 0 ) out f;
	#if OS_LINUX
		i4 fd = open( path, O_RDONLY );
		out_if( fd is -1 ) f;
		anon ref mapped = mmap( nothing, f.size, PROT_READ, MAP_PRIVATE, fd, 0 );
		close( fd );
		out_if( mapped is MAP_FAILED ) f;
		f.mapped_bytes = to( byte ref, mapped );
	#elif OS_WINDOWS
		HANDLE hf = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, nothing, OPEN_EXISTING, 0, nothing );
		out_if( hf is INVALID_HANDLE_VALUE ) f;
		HANDLE hm = CreateFileMapping( hf, nothing, PAGE_READONLY, 0, 0, nothing );
		CloseHandle( hf );
		if_nothing( hm ) out f;
		f.mapped_bytes = to( byte ref, MapViewOfFile( hm, FILE_MAP_READ, 0, 0, 0 ) );
		CloseHandle( hm );
	#endif
	f.path_size = path_size;
	bytes_copy( f.path, path, f.path_size );
	out f;
}

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | os / visible

////////////////
#pragma region | - ref

#define os_create_ref( TYPE, AMOUNT... ) to( TYPE ref, _alloc( size_of( TYPE ) * DEFAULT( 1, AMOUNT ) ) )
#define os_delete_ref( REF ) START_DEF { skip_if_nothing( REF ); _free( REF ); REF = nothing; } END_DEF
#define os_resize_ref( REF, NEW_SIZE, PRESERVE ) to( type_of( REF ), _ref_resize( REF, NEW_SIZE, PRESERVE ) )

#pragma endregion

////////////////
#pragma region | - command

#if OS_WINDOWS and not defined( _IO_H_ )
	__declspec( dllimport ) i8 __cdecl _open_osfhandle( i8 osfhandle, i4 flags );
#endif

#define command( COMMAND ) system( COMMAND )
#define command_read_open( COMMAND ) popen( COMMAND, "r" )
#define command_read_close( OS_FILE_HANDLE ) pclose( OS_FILE_HANDLE )

embed out_state command_silent( byte const ref const command, flag const detach )
{
	#if OS_LINUX
		byte command_bytes[ 1024 ] = { 0 };
		byte ref command_bytes_ref = command_bytes;
		bytes_paste_move( command_bytes_ref, pick( detach is yes, "setsid ", "" ) );
		bytes_paste_move( command_bytes_ref, command );
		bytes_paste_move( command_bytes_ref, pick( detach is yes, " </dev/null >/dev/null 2>&1 &", " >/dev/null 2>&1" ) );
		out to( out_state, WEXITSTATUS( command( command_bytes ) ) );
	#elif OS_WINDOWS
		byte command_bytes[ 1024 ] = { 0 };
		byte ref command_bytes_ref = command_bytes;
		bytes_paste_move( command_bytes_ref, "cmd.exe /c \"" );
		bytes_paste_move( command_bytes_ref, command );
		bytes_paste_move( command_bytes_ref, "\"" );

		STARTUPINFOA si = { sizeof( si ) };
		PROCESS_INFORMATION pi;
		if( not CreateProcessA( nothing, command_bytes, nothing, nothing, FALSE, detach is yes ? DETACHED_PROCESS : CREATE_NO_WINDOW, nothing, nothing, ref_of( si ), ref_of( pi ) ) )
		{
			out -1;
		}
		DWORD exit_code = 0;
		if( detach is no )
		{
			WaitForSingleObject( pi.hProcess, INFINITE );
			GetExitCodeProcess( pi.hProcess, ref_of( exit_code ) );
		}
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
		out to( out_state, exit_code );
	#endif
}
#define command_silent( COMMAND, DETACH... ) command_silent( COMMAND, DEFAULT( no, DETACH ) )

embed os_handle command_read_open_silent( byte const ref const command )
{
	#if OS_LINUX
		byte command_bytes[ 1024 ] = { 0 };
		byte ref command_bytes_ref = command_bytes;
		bytes_paste_move( command_bytes_ref, command );
		bytes_paste_move( command_bytes_ref, " 2>/dev/null" );
		out command_read_open( command_bytes );
	#elif OS_WINDOWS
		byte command_bytes[ 1024 ] = { 0 };
		byte ref command_bytes_ref = command_bytes;
		bytes_paste_move( command_bytes_ref, "cmd.exe /c \"" );
		bytes_paste_move( command_bytes_ref, command );
		bytes_paste_move( command_bytes_ref, "\"" );

		SECURITY_ATTRIBUTES sa = { sizeof( sa ), nothing, TRUE };
		HANDLE read_handle;
		HANDLE write_handle;
		if( not CreatePipe( ref_of( read_handle ), ref_of( write_handle ), ref_of( sa ), 0 ) )
		{
			out nothing;
		}
		SetHandleInformation( read_handle, HANDLE_FLAG_INHERIT, 0 );

		HANDLE null_in = CreateFileA( "NUL", GENERIC_READ, FILE_SHARE_READ, ref_of( sa ), OPEN_EXISTING, 0, nothing );

		STARTUPINFOA si = { sizeof( si ), .dwFlags = STARTF_USESTDHANDLES, .hStdInput = null_in, .hStdOutput = write_handle, .hStdError = write_handle };
		PROCESS_INFORMATION pi;
		if( not CreateProcessA( nothing, command_bytes, nothing, nothing, TRUE, CREATE_NO_WINDOW, nothing, nothing, ref_of( si ), ref_of( pi ) ) )
		{
			CloseHandle( read_handle );
			CloseHandle( write_handle );
			CloseHandle( null_in );
			out nothing;
		}

		CloseHandle( write_handle );
		CloseHandle( null_in );
		CloseHandle( pi.hThread );
		CloseHandle( pi.hProcess );

		out _fdopen( _open_osfhandle( to( intptr_t, read_handle ), 0 ), "r" );
	#endif
}

#define command_read_close_silent( OS_FILE_HANDLE ) OS_PICK( command_read_close( OS_FILE_HANDLE ), fclose( OS_FILE_HANDLE ) )

fn command_get_input( byte ref const bytes, n2 const bytes_size )
{
	os_handle_get_line( bytes, bytes_size, stdin );
	n2 const input_size = bytes_measure( bytes );
	out_if( input_size is 0 );
	bytes[ input_size - 1 ] = eof_byte;
}

#pragma endregion

////////////////
#pragma region | - print

#define print( BYTES ) fputs( BYTES, stdout )
#define print_count( BYTES, SIZE ) fwrite( BYTES, 1, SIZE, stdout )
#define print_show() fflush( stdout )
#define print_clear() system( OS_PICK( "clear", "cls" ) )

#define print_newline() print_count( newline, 1 )
#define print_separator() print_count( separator, 1 )
#define print_tab() print_count( tab, 1 )

#pragma endregion

////////////////
#pragma region | - path

#define path( FOLDERS... ) CHAIN(,, separator, FOLDERS )

embed n2 const program_get_path( byte ref const out_bytes )
{
	#if OS_LINUX
		n2 const size = readlink( "/proc/self/exe", out_bytes, path_max_size );
		out_if( size is -1 ) 0;

		if( size is path_max_size )
		{
			out_bytes[ path_max_size - 1 ] = eof_byte;
		}
		else
		{
			out_bytes[ size ] = eof_byte;
		}
		out size;
	#elif OS_WINDOWS
		out GetModuleFileNameA( nothing, out_bytes, path_max_size );
	#endif
}

fn path_up_folder( byte ref const path )
{
	byte ref path_end = path + bytes_measure( path );
	while( path_end > path and val_of( --path_end ) isnt '\\' and val_of( path_end ) isnt '/' );
	if( path_end > path )
	{
		val_of( path_end ) = eof_byte;
	}
}

embed byte ref const path_get_name( byte ref const path )
{
	byte ref path_end = path + bytes_measure( path );
	while( path_end > path and val_of( --path_end ) isnt '\\' and val_of( path_end ) isnt '/' );
	if( path_end > path )
	{
		++path_end;
	}
	out path_end;
}

embed byte ref const path_get_extension( byte ref const path )
{
	byte ref path_end = path + bytes_measure( path );
	while( path_end > path and val_of( --path_end ) isnt '.' );
	if( path_end > path )
	{
		++path_end;
	}
	out path_end;
}

#pragma endregion

////////////////
#pragma region | - entries

embed n2 os_get_entries( byte const ref const folder_path, byte entries[][ path_max_size ], n2 const max_entries, entry_type const type, flag const folder_separator )
{
	n2 count = 0;
	n2 folder_path_size = bytes_measure( folder_path );
	byte path[ path_max_size ] = { 0 };
	bytes_paste( path, folder_path );

	OS_PICK( struct dirent ref, WIN32_FIND_DATA ) entry;
	#if OS_LINUX
		struct stat stat_buf;
		path[ folder_path_size++ ] = '/';
	#elif OS_WINDOWS
		bytes_copy( path + folder_path_size, "\\*", 3 );
		flag first = yes;
	#endif
	anon ref const handle = OS_PICK( opendir( path ), FindFirstFile( path, ref_of( entry ) ) );
	out_if( handle is OS_PICK( 0, INVALID_HANDLE_VALUE ) ) 0;

	while( count < max_entries )
	{
		#if OS_LINUX
			skip_if( ( entry = readdir( handle ) ) is 0 );
		#elif OS_WINDOWS
			if( first )
			{
				first = no;
			}
			else skip_if( FindNextFile( handle, ref_of( entry ) ) is 0 );
		#endif

		byte const ref entry_name = OS_PICK( entry->d_name, entry.cFileName );
		next_if( entry_name[ 0 ] is '.' );

		n2 const entry_size = bytes_measure( entry_name ) + 1;

		#if OS_LINUX
			bytes_copy( path + folder_path_size, entry_name, entry_size );
			next_if( stat( path, ref_of( stat_buf ) ) isnt 0 );
		#endif

		flag const is_dir = OS_PICK( S_ISDIR( stat_buf.st_mode ), entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY );
		next_if( type isnt entry_any and is_dir isnt ( type is entry_folders ) );

		bytes_copy( entries[ count ], entry_name, entry_size );
		if( is_dir and folder_separator )
		{
			entries[ count ][ entry_size - 1 ] = separator_byte;
			entries[ count ][ entry_size ] = eof_byte;
		}
		++count;
	}

	OS_PICK( closedir( handle ), FindClose( handle ) );
	out count;
}

#define os_get_files( PATH, OUT_ENTRIES, MAX_ENTRIES ) os_get_entries( PATH, OUT_ENTRIES, MAX_ENTRIES, entry_files, no )
#define os_get_folders( PATH, OUT_ENTRIES, MAX_ENTRIES, FOLDER_SEPARATOR... ) os_get_entries( PATH, OUT_ENTRIES, MAX_ENTRIES, entry_folders, DEFAULT( yes, FOLDER_SEPARATOR ) )

#pragma endregion

////////////////
#pragma region | - file

embed flag os_file_exists( byte const ref const path )
{
	#if OS_LINUX
		struct stat st;
		out stat( path, ref_of( st ) ) is 0 and S_ISREG( st.st_mode );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out attrib isnt INVALID_FILE_ATTRIBUTES and not( attrib & FILE_ATTRIBUTE_DIRECTORY );
	#endif
}

#define os_create_file( PATH, PATH_SIZE... ) _os_file_saving( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )
#define os_open_file( PATH, PATH_SIZE... ) _os_file_loading( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )
#define os_map_file( PATH, PATH_SIZE... ) _os_map_file( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )

fn os_delete_file( const byte ref const path )
{
	remove( path );
}

fn os_file_ref_save( os_file ref const file_ref, byte const ref const bytes, n8 const size )
{
	if_nothing( file_ref->handle ) out;
	fseek( file_ref->handle, 0, SEEK_SET );
	file_ref->size = size;
	fwrite( bytes, 1, file_ref->size, file_ref->handle );
	fflush( file_ref->handle );
}

fn os_file_ref_load( os_file ref const file_ref, byte ref const out_bytes )
{
	if_nothing( file_ref->handle ) out;
	fseek( file_ref->handle, 0, SEEK_SET );
	fread( out_bytes, 1, file_ref->size, file_ref->handle );
}

fn os_file_ref_clear( os_file ref const file_ref )
{
	file_ref->handle = nothing;
	bytes_clear( file_ref->path, file_ref->path_size );
	file_ref->path_size = 0;
	file_ref->size = 0;
}

fn os_file_ref_close( os_file ref const file_ref )
{
	if_something( file_ref->handle ) fclose( file_ref->handle );
	os_file_ref_clear( file_ref );
}

fn os_file_ref_unmap( os_file ref const file_ref )
{
	if_something( file_ref->mapped_bytes )
	{
		#if OS_LINUX
			munmap( to( anon ref, file_ref->mapped_bytes ), file_ref->size );
		#elif OS_WINDOWS
			UnmapViewOfFile( file_ref->mapped_bytes );
		#endif
	}
	os_file_ref_clear( file_ref );
}

#pragma endregion

////////////////
#pragma region | - folder

fn os_create_folder( byte const ref const path )
{
	#if OS_LINUX
		mkdir( path, 0755 );
	#else
		CreateDirectoryA( path, nothing );
	#endif
}

embed flag os_folder_exists( byte const ref const path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISDIR( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD const attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and ( attrib & FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

fn os_delete_folder( byte const ref const path )
{
	out_if( not os_folder_exists( path ) );

	byte cmd[ path_max_size + 32 ];
	byte ref cmd_ref = cmd;
	#if OS_LINUX
		bytes_paste_move( cmd_ref, "rm -rf \"" );
		bytes_paste_move( cmd_ref, path );
		bytes_paste_move( cmd_ref, "\"" );
	#else
		bytes_paste_move( cmd_ref, "rmdir /s /q \"" );
		bytes_paste_move( cmd_ref, path );
		bytes_paste_move( cmd_ref, "\" 2>nul" );
	#endif
	bytes_end( cmd_ref );
	command_silent( cmd );
}

#pragma endregion

////////////////
#pragma region | - sleep

#if OS_LINUX
	#define sleep( MILLISECONDS ) usleep( ( MILLISECONDS ) * 1000 )
#elif OS_WINDOWS
	#define sleep( MILLISECONDS ) Sleep( MILLISECONDS )
#endif

#pragma endregion

#pragma endregion visible

#pragma endregion os

////////////////////////////////////////////////////////////////
#pragma region - mathematics

////////////////////////////////
#pragma region | mathematics / hidden

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
	embed r##N r##N##_median4( r##N const a, r##N const b, r##N const c, r##N const d )\
	{\
		out MEDIAN4( a, b, c, d );\
	}\
	embed r##N r##N##_avg( r##N const a, r##N const b )\
	{\
		out AVG( a, b );\
	}\
	embed r##N r##N##_avg4( r##N const a, r##N const b, r##N const c, r##N const d )\
	{\
		out AVG4( a, b, c, d );\
	}\
	embed r##N r##N##_mix( r##N const a, r##N const b, r##N const amount )\
	{\
		out MIX( a, b, amount );\
	}\
	embed r##N r##N##_map( r##N const v, r##N const from_lower, r##N const from_upper, r##N const to_lower, r##N const to_upper )\
	{\
		out MAP( v, from_lower, from_upper, to_lower, to_upper );\
	}\
	embed r##N r##N##_range( r##N const v, r##N const lower, r##N const upper )\
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
	embed r##N r##N##_random_range( r##N const minimum, r##N const maximum )\
	{\
		out minimum + r##N##_random_unit() * ( maximum - minimum );\
	}
#pragma endregion hidden

////////////////////////////////
#pragma region | mathematics / visible

////////////////
#pragma region | - 1 byte

FUNCTION_GROUP_N( 1 );
FUNCTION_GROUP_I( 1 );

#pragma endregion

////////////////
#pragma region | - 2 bytes

FUNCTION_GROUP_N( 2 );
FUNCTION_GROUP_I( 2 );

#pragma endregion

////////////////
#pragma region | - 4 bytes

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

#pragma endregion

////////////////
#pragma region | - 8 bytes

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

#pragma endregion

#pragma endregion visible

#pragma endregion mathematics

#pragma endregion definitions

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - START
//

#define _start_fn out_state main( i4 const start_inputs_count, byte const ref const ref const start_inputs )
#define start _start_fn

#pragma endregion start

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
