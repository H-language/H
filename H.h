/////// /////// /////// /////// /////// /////// ///////
//
//  H - v0.1 - @ENDESGA - 2025 - Made in NZ - CC0 - foss forever
//
/////// /////// /////// /////// /////// /////// ///////

#pragma once

///////

#define OS_LINUX 0
#define OS_WINDOWS 0
#define OS_MACOS 0
#define OS_UNKNOWN 0
//
#if defined( __linux__ )
	#undef OS_LINUX
	#define OS_LINUX 1
	#define OS_NAME "Linux"
	#if __BYTE_ORDER == __LITTLE_ENDIAN
		#define IS_BIG_ENDIAN 0
	#elif __BYTE_ORDER == __BIG_ENDIAN
		#define IS_BIG_ENDIAN 1
	#endif
	#define _GNU_SOURCE
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <dirent.h>
	#include <time.h>
	#include <fcntl.h>
	#include <pthread.h>
	#include <unistd.h>
	#ifdef C7H16
		#include <alsa/asoundlib.h>
		#include <X11/Xlib.h>
		#include <X11/Xutil.h>
		#include <X11/extensions/Xrender.h>
		#include <X11/extensions/Xpresent.h>
		#include <X11/XKBlib.h>
	#endif
	//
#elif defined( _WIN32 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
	#define OS_NAME "Windows"
	#define IS_BIG_ENDIAN 0
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>
	//
#elif defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
	#define OS_NAME "macOS"
	#define IS_BIG_ENDIAN 0
	//
#else
	#undef OS_UNKNOWN
	#define OS_UNKNOWN 1
	#define OS_NAME "unknown"
#endif

///////

#define COMPILER_GCC 0
#define COMPILER_TCC 0
#define COMPILER_CLANG 0
#define COMPILER_MSVC 0
#define COMPILER_UNKNOWN 0
//
#if defined( __clang__ )
	#undef COMPILER_CLANG
	#define COMPILER_CLANG 1
	#define COMPILER_NAME "Clang"
	//
#elif defined( __TINYC__ )
	#undef COMPILER_TCC
	#define COMPILER_TCC 1
	#define COMPILER_NAME "TCC"
	//
#elif defined( __GNUC__ )
	#undef COMPILER_GCC
	#define COMPILER_GCC 1
	#define COMPILER_NAME "GCC"
	//
#elif defined( _MSC_VER )
	#undef COMPILER_MSVC
	#define COMPILER_MSVC 1
	#define COMPILER_NAME "MSVC"
	//
#else
	#undef COMPILER_UNKNOWN
	#define COMPILER_UNKNOWN 1
	#define COMPILER_NAME "unknown"
#endif

///////

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

///////

#define START_DEF do
#define END_DEF while( 0 )
//
#define REQUIRE_SEMICOLON START_DEF {} END_DEF

///////

#define _EVAL( ARGS... ) ARGS
#define EVAL( ARGS... ) _EVAL( ARGS )
#define _JOIN( A, B... ) A##B
#define JOIN( A, B... ) _JOIN( A, B )
//
#define SKIP_ARG( _, ARGS... ) ARGS
//
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
//
#define COMMA ,
//
#define _PASTE_IF_ARGS_EVAL( CODE, ARGS... ) GET_ARG2( ARGS, EVAL CODE )
#define _PASTE_IF_ARGS( CODE, ARGS... ) _PASTE_IF_ARGS_EVAL( CODE, GET_ARG1 ARGS( COMMA ) )
#define PASTE_IF_ARGS( CODE, ARGS... ) _PASTE_IF_ARGS( ( CODE ), GET_ARG1( ARGS ) )
//
#define COMMA_IF_ARGS( ARGS... ) PASTE_IF_ARGS( COMMA, ARGS )
//
#define _COUNT_ARGS_EVAL( ARGS... ) GET_ARG17( ARGS, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 )
#define COUNT_ARGS( ARGS... ) _COUNT_ARGS_EVAL( ARGS COMMA_IF_ARGS( ARGS ) 16 )

///////

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

///////

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

///////

#define _AS_BYTES( VALUE ) #VALUE
#define AS_BYTES( VALUE ) _AS_BYTES( VALUE )

///////

#define ref *
#define const_ref ref const
#define temp register
#define perm static
#define global perm

#if OS_LINUX
	#define cache_align __attribute__( ( aligned( 64 ) ) )
#else
	#define cache_align __declspec( align( 64 ) )
#endif

///////

#define type_from( TYPE... ) typedef TYPE
#define ref_of( VAR... ) ( & ( VAR ) )
#define val_of( REF... ) ( * ( REF ) )
#define to( TYPE, VAL... ) ( TYPE ) ( VAL )
#define cast( TYPE, VAR... ) val_of( to( TYPE ref, ref_of( VAR ) ) )
//
#define anon void
#define nothing to( anon ref, 0 )
//
#define size_of( TYPE... ) sizeof( TYPE )
#define type_of( VAR... ) typeof( VAR )
#define type_of_ref( REF... ) type_of( val_of( to( type_of( REF ), nothing ) ) )

///////

type_from( _Bool ) flag;
#define flag( ARGS... ) to( flag, !! ( ARGS ) )
#define yes 1
#define no 0
#define flip( FLAG ) FLAG ^= 1
//
#define not !
#define and &&
#define or ||
#define xor ^
#define mod %
#define is ==
#define isnt !=
#define is_even mod 2 is 0
#define is_odd mod 2 isnt 0

///////

#define embed perm inline __attribute__( ( always_inline ) )
#define fn embed anon
#define out return
//
#define fn_ref( OUTPUT, NAME, ARG_TYPES... ) OUTPUT( ref NAME ) ( ARG_TYPES )
#define fn_type( OUTPUT, ARG_TYPES... ) type_from( type_of( fn_ref( DEFAULTS( ( anon ), OUTPUT ),, ARG_TYPES ) ) )

///////

#define loop for( ;; )
#define next continue
#define skip break
#define jump goto
#define until( ARGS... ) while( not( ARGS ) )
//
// thank you Dad for the with/when suggestion:
#define with switch
#define when( ARGS... ) CHAIN( case, :,, ARGS )
#define other default:
//
#define pick( IF_YES, THEN_THIS, ELSE_THIS ) ( ( IF_YES ) ? ( THEN_THIS ) : ( ELSE_THIS ) )
#define PICK_0( THEN_THIS, ELSE_THIS ) ELSE_THIS
#define PICK_1( THEN_THIS, ELSE_THIS ) THEN_THIS
#define PICK( IF_1, THEN_THIS, ELSE_THIS ) JOIN( PICK_, IF_1 ) ( THEN_THIS, ELSE_THIS )
//
#define _once( _ONCE_ )\
	perm flag _ONCE_ = yes;\
	if( _ONCE_ and( _ONCE_ = no, yes ) )
#define once _once( JOIN( _ONCE_, __COUNTER__ ) )

///////

#define _range( POS_NAME, FROM, TO, STEP, SYMBOL_COMPARE, SYMBOL_STEP ) for( temp i8 POS_NAME = i8( FROM ); POS_NAME SYMBOL_COMPARE i8( TO ); POS_NAME SYMBOL_STEP i8( STEP ) )

#define range_step( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, <=, += )
#define range_step_inv( POS_NAME, FROM, TO, STEP ) _range( POS_NAME, FROM, TO, STEP, >=, -= )

#define range( POS_NAME, FROM, TO ) range_step( POS_NAME, FROM, TO, 1 )
#define range_inv( POS_NAME, FROM, TO ) range_step_inv( POS_NAME, FROM, TO, 1 )

#define range_grid( X_NAME, Y_NAME, X_FROM, X_TO, Y_FROM, Y_TO ) range( Y_NAME, Y_FROM, Y_TO ) range( X_NAME, X_FROM, X_TO )

#define iter_step( POS_NAME, SIZE, STEP ) _range( POS_NAME, 0, SIZE, STEP, <, += )
#define iter_step_inv( POS_NAME, SIZE, STEP ) _range( POS_NAME, SIZE, 0, STEP, >, -= )

#define iter( POS_NAME, SIZE ) _range( POS_NAME, 0, SIZE, 1, <, += )
#define iter_inv( POS_NAME, SIZE ) _range( POS_NAME, SIZE, 0, 1, >, -= )

#define iter_grid( X_NAME, Y_NAME, WIDTH, HEIGHT ) iter( Y_NAME, HEIGHT ) iter( X_NAME, WIDTH )

#define _repeat( N_TIMES, COUNTER ) iter( JOIN( _REP_, COUNTER ), N_TIMES )
#define repeat( N_TIMES ) _repeat( N_TIMES, __COUNTER__ )

///////

#define if_nothing( ARG... ) if( ARG is nothing )
#define if_something( ARG... ) if( ARG isnt nothing )
//
#define any( ARGS... ) ( CHAIN_PAREN(,, or, ARGS ) )
#define all( ARGS... ) ( CHAIN_PAREN(,, and, ARGS ) )
#define none( ARGS... ) ( not any( ARGS ) )
#define not_all( ARGS... ) ( not all( ARGS ) )
//
#define if_any( ARGS... ) if any( ARGS )
#define if_all( ARGS... ) if all( ARGS )
#define if_none( ARGS... ) if none( ARGS )
#define if_not_all( ARGS... ) if not_all( ARGS )
//
#define while_any( ARGS... ) while any( ARGS )
#define while_all( ARGS... ) while all( ARGS )
#define while_none( ARGS... ) while none( ARGS )
#define while_not_all( ARGS... ) while not_all( ARGS )
//
#define skip_if( ARG... ) if( ARG ) skip
#define skip_if_nothing( ARG... ) if_nothing( ARG ) skip
#define skip_if_something( ARG... ) if_something( ARG ) skip
#define skip_if_any( ARGS... ) if_any( ARGS ) skip
#define skip_if_all( ARGS... ) if_all( ARGS ) skip
#define skip_if_none( ARGS... ) if_none( ARGS ) skip
#define skip_if_not_all( ARGS... ) if_not_all( ARGS ) skip
//
#define jump_if( ARG... ) if( ARG ) jump
#define jump_if_nothing( ARG... ) if_nothing( ARG ) jump
#define jump_if_something( ARG... ) if_something( ARG ) jump
#define jump_if_any( ARGS... ) if_any( ARGS ) jump
#define jump_if_all( ARGS... ) if_all( ARGS ) jump
#define jump_if_none( ARGS... ) if_none( ARGS ) jump
#define jump_if_not_all( ARGS... ) if_not_all( ARGS ) jump
//
#define next_if( ARG... ) if( ARG ) next
#define next_if_nothing( ARG... ) if_nothing( ARG ) next
#define next_if_something( ARG... ) if_something( ARG ) next
#define next_if_any( ARGS... ) if_any( ARGS ) next
#define next_if_all( ARGS... ) if_all( ARGS ) next
#define next_if_none( ARGS... ) if_none( ARGS ) next
#define next_if_not_all( ARGS... ) if_not_all( ARGS ) next
//
#define out_if( ARG... ) if( ARG ) out
#define out_if_nothing( ARG... ) if_nothing( ARG ) out
#define out_if_something( ARG... ) if_something( ARG ) out
#define out_if_any( ARGS... ) if_any( ARGS ) out
#define out_if_all( ARGS... ) if_all( ARGS ) out
#define out_if_none( ARGS... ) if_none( ARGS ) out
#define out_if_not_all( ARGS... ) if_not_all( ARGS ) out

///////

type_from( char ) byte;
#define byte( VAL ) to( byte, VAL )
#define size_of_bytes( BYTES ) ( size_of( BYTES ) - 1 )

///////
// natural 1/2/4/8, integer 1/2/4/8, rational 4/8
//
// 1 byte
type_from( unsigned char ) n1;
#define n1( VAL ) to( n1, VAL )
#define min_n1 n1( 0x00u )
#define max_n1 n1( 0xFFu )
//
type_from( signed char ) i1;
#define i1( VAL ) to( i1, VAL )
#define min_i1 i1( 0x80 )
#define max_i1 i1( 0x7F )
//
// 2 bytes
type_from( unsigned short ) n2;
#define n2( VAL ) to( n2, VAL )
#define min_n2 n2( 0x0000u )
#define max_n2 n2( 0xFFFFu )
//
type_from( signed short ) i2;
#define i2( VAL ) to( i2, VAL )
#define min_i2 i2( 0x8000 )
#define max_i2 i2( 0x7FFF )
//
// 4 bytes
type_from( unsigned int ) n4;
#define n4( VAL ) to( n4, VAL )
#define min_n4 n4( 0x00000000u )
#define max_n4 n4( 0xFFFFFFFFu )
//
type_from( signed int ) i4;
#define i4( VAL ) to( i4, VAL )
#define min_i4 i4( 0x80000000 )
#define max_i4 i4( 0x7FFFFFFF )
//
type_from( float ) r4;
#define r4( VAL ) to( r4, VAL )
//
// 8 bytes
type_from( unsigned long long ) n8;
#define n8( VAL ) to( n8, VAL )
#define min_n8 n8( 0x0000000000000000u )
#define max_n8 n8( 0xFFFFFFFFFFFFFFFFu )
//
type_from( signed long long ) i8;
#define i8( VAL ) to( i8, VAL )
#define min_i8 i8( 0x8000000000000000 )
#define max_i8 i8( 0x7FFFFFFFFFFFFFFF )
//
type_from( double ) r8;
#define r8( VAL ) to( r8, VAL )

///////

type_from( i4 ) out_state;
#define success 0
#define failure 1
#define warning 2

///////

#define n_to_bits( N ) pick( ( N ) <= 1, 1, ( 32 - __builtin_clz( ( N ) - 1 ) ) )

///////

#define new_ref( TYPE, AMOUNT... ) to( TYPE ref, calloc( DEFAULT( 1, AMOUNT ), size_of( TYPE ) ) )
#define new_bytes( AMOUNT... ) malloc( DEFAULT( 1, AMOUNT ) )

#define delete_ref free

#define bytes_copy( FROM_REF, FROM_SIZE, TO_REF ) memcpy( TO_REF, FROM_REF, FROM_SIZE )
#define bytes_copy_until( FROM_REF, TO_REF, CHAR, MAX_SIZE ) memccpy( TO_REF, FROM_REF, CHAR, MAX_SIZE )
#define bytes_copy_until_any( FROM_REF, TO_REF, DELIMS ) memcpy( TO_REF, FROM_REF, strcspn( FROM_REF, DELIMS ) )
#define bytes_move( FROM_REF, FROM_SIZE, TO_REF ) memmove( TO_REF, FROM_REF, FROM_SIZE )
#define bytes_paste( FROM_REF, TO_REF ) strcpy( TO_REF, FROM_REF )
#define bytes_fill( REF, VAL, SIZE ) memset( REF, VAL, SIZE )
#define bytes_clear( REF, SIZE ) bytes_fill( REF, 0, SIZE )
#define bytes_compare( A, B, AMOUNT ) memcmp( A, B, AMOUNT )
#define bytes_measure( REF ) strlen( REF )

#define bytes_copy_move( FROM_REF, FROM_SIZE, TO_REF )\
	START_DEF\
	{\
		bytes_copy( FROM_REF, FROM_SIZE, TO_REF );\
		TO_REF += FROM_SIZE;\
	}\
	END_DEF

#define bytes_paste_move( FROM_REF, TO_REF )\
	START_DEF\
	{\
		temp const byte const_ref _FROM_REF = FROM_REF;\
		temp const n2 _PASTE_SIZE = bytes_measure( _FROM_REF );\
		bytes_copy_move( _FROM_REF, _PASTE_SIZE, TO_REF );\
	}\
	END_DEF

#define bytes_set_move( BYTE, TO_REF ) val_of( TO_REF++ ) = BYTE

#define bytes_newline_move( TO_REF ) bytes_set_move( newline_byte, TO_REF )
#define bytes_separator_move( TO_REF ) bytes_set_move( separator_byte, TO_REF )

#define bytes_end( BYTES ) val_of( BYTES ) = '\0'

embed anon const_ref _ref_resize( anon ref r, size_t type_size, size_t old_count, size_t new_count )
{
	temp anon const_ref new_ptr = realloc( r, type_size * new_count );
	if( new_ptr isnt nothing and new_count > old_count )
	{
		bytes_clear( to( byte ref, new_ptr ) + ( type_size * old_count ), type_size * ( new_count - old_count ) );
	}
	out new_ptr;
}
#define ref_resize( REF, OLD_COUNT, NEW_COUNT ) _ref_resize( REF, size_of( type_of_ref( REF ) ), OLD_COUNT, NEW_COUNT )

#define bytes_resize( REF, NEW_SIZE... ) realloc( REF, DEFAULT( 1, NEW_SIZE ) )

#define bytes_add( BYTES, BYTE ) val_of( BYTES++ ) = BYTE

#define bytes_add_bytes( DST, SRC, SIZE )\
	START_DEF\
	{\
		temp n1 _i = 0;\
		while( _i < ( SIZE ) ) val_of( DST++ ) = ( SRC )[ _i++ ];\
	}\
	END_DEF

///////

#define packed __attribute__( ( packed ) )

#define variant struct

#define _type_make( NAME, REF, EXTRA... )\
	type_from( struct NAME REF ) NAME;\
	EXTRA;\
	struct NAME
#define type( NAME ) _type_make( NAME, )

#define make( TYPE, ELEMENT_VALUES... ) ( ( TYPE ) { ELEMENT_VALUES } )

#define object( NAME ) _type_make( NAME, ref, fn_type(, NAME this ) NAME##_fn; )
#define object_fn( OBJECT, FN, ARGS... )\
	fn OBJECT##_##FN( const OBJECT this COMMA_IF_ARGS( ARGS ) ARGS )
#define new_object_fn( OBJECT, ARGS... )\
	embed OBJECT new_##OBJECT( ARGS )

#define call( OBJECT, FN ) if_something( OBJECT->FN ) OBJECT->FN( OBJECT )

#define new_object( OBJECT ) new_ref( type_of_ref( OBJECT ) )

//

#define fusion( NAME )\
	type_from( union NAME ) NAME;\
	union NAME

#define group( NAME, TYPE... )\
	type_from( DEFAULT( byte, TYPE ) ) NAME;\
	enum NAME

///////

#define print( BYTES ) fputs( BYTES, stdout )
#define print_size( BYTES, SIZE ) fwrite( BYTES, 1, SIZE, stdout )
#define print_show() fflush( stdout )

#define newline "\n"
#define newline_byte '\n'

#define separator PICK( OS_LINUX, "/", "\\" )
#define separator_byte PICK( OS_LINUX, '/', '\\' )

#define print_newline() print_size( newline, 1 )

///////

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
#define SNAP( V, MULTIPLES_OF ) ( ( V ) / ( MULTIPLES_OF ) ) * ( MULTIPLES_OF )
#define SNAP_r( N, V, MULTIPLES_OF ) r##N##_trunc( ( V ) / ( MULTIPLES_OF ) ) * ( MULTIPLES_OF )
#define SNAP_BIT( V, BIT ) ( ( ( V ) >> ( BIT ) ) << ( BIT ) )

#define MIX( A, B, AMOUNT ) ( ( A ) + ( AMOUNT ) * ( ( B ) - ( A ) ) )
#define MAP( V, A, B, C, D ) ( ( V ) - ( A ) ) * ( ( D ) - ( C ) ) / ( ( B ) - ( A ) ) + ( C )
#define RANGE( V, LOWER, UPPER ) ( ( V - ( LOWER ) ) / ( ( UPPER ) - ( LOWER ) ) )

#define TRUNC_r( N, ... ) r##N( i##N( __VA_ARGS__ ) )
#define FLOOR_r( N, ... ) pick( __VA_ARGS__ >= 0, TRUNC_r( N, __VA_ARGS__ ), r##N( i##N( __VA_ARGS__ ) - 1 ) )
#define ROUND_r( N, ... ) TRUNC_r( N, __VA_ARGS__ + pick( __VA_ARGS__ >= 0, 0.5, -0.5 ) )
#define CEIL_r( N, ... ) pick( __VA_ARGS__ > 0, r##N( i##N( __VA_ARGS__ ) + 1 ), TRUNC_r( N, __VA_ARGS__ ) )
#define MOD_r( N, V, MODULO ) ( ( V ) - ( MODULO ) * r##N##_floor( ( V ) / ( MODULO ) ) )

#define SMOOTH( V ) pick( ( V ) <= 0., 0, pick( ( V ) >= 1., 1, ( V ) * ( V ) * ( 3 - 2 * ( V ) ) ) )

// // // // // // //

#define FUNCTION_GROUP_BASE( T, N )\
	embed T##N T##N##_min( const T##N a, const T##N b )\
	{\
		out MIN( a, b );\
	}\
	embed T##N T##N##_min3( const T##N a, const T##N b, const T##N c )\
	{\
		out MIN3( a, b, c );\
	}\
	embed T##N T##N##_min4( const T##N a, const T##N b, const T##N c, const T##N d )\
	{\
		out MIN4( a, b, c, d );\
	}\
	embed T##N T##N##_min5( const T##N a, const T##N b, const T##N c, const T##N d, const T##N e )\
	{\
		out MIN5( a, b, c, d, e );\
	}\
	embed T##N T##N##_max( const T##N a, const T##N b )\
	{\
		out MAX( a, b );\
	}\
	embed T##N T##N##_max3( const T##N a, const T##N b, const T##N c )\
	{\
		out MAX3( a, b, c );\
	}\
	embed T##N T##N##_max4( const T##N a, const T##N b, const T##N c, const T##N d )\
	{\
		out MAX4( a, b, c, d );\
	}\
	embed T##N T##N##_max5( const T##N a, const T##N b, const T##N c, const T##N d, const T##N e )\
	{\
		out MAX5( a, b, c, d, e );\
	}\
	embed T##N T##N##_median( const T##N a, const T##N b, const T##N c )\
	{\
		out MEDIAN( a, b, c );\
	}\
	embed T##N T##N##_median5( const T##N a, const T##N b, const T##N c, const T##N d, const T##N e )\
	{\
		out MEDIAN5( a, b, c, d, e );\
	}\
	embed T##N T##N##_avg3( const T##N a, const T##N b, const T##N c )\
	{\
		out AVG3( a, b, c );\
	}\
	embed T##N T##N##_clamp( const T##N v, const T##N min, const T##N max )\
	{\
		out CLAMP( v, min, max );\
	}\
	embed T##N T##N##_saturate( const T##N v )\
	{\
		out SATURATE( v );\
	}\
	embed T##N T##N##_sqr( const T##N v )\
	{\
		out SQR( v );\
	}\
	embed T##N T##N##_cube( const T##N v )\
	{\
		out CUBE( v );\
	}

#define FUNCTION_GROUP_BASE_NI( T, N )\
	embed T##N T##N##_median4( const T##N a, const T##N b, const T##N c, const T##N d )\
	{\
		out MEDIAN4_BITWISE( a, b, c, d );\
	}\
	embed T##N T##N##_avg( const T##N a, const T##N b )\
	{\
		out AVG_BITWISE( a, b );\
	}\
	embed T##N T##N##_avg4( const T##N a, const T##N b, const T##N c, const T##N d )\
	{\
		out AVG4_BITWISE( a, b, c, d );\
	}\
	embed T##N T##N##_snap( const T##N v, const T##N multiples_of )\
	{\
		out SNAP( v, multiples_of );\
	}\
	embed T##N T##N##_snap_bit( const T##N v, const T##N b )\
	{\
		out SNAP_BIT( v, b );\
	}\
	embed T##N T##N##_random()\
	{\
		out T##N( rand() );\
	}\
	embed T##N T##N##_random_range( const T##N minimum, const T##N maximum )\
	{\
		out minimum + T##N( ( r4( rand() ) / r4( RAND_MAX ) ) * r4( maximum - minimum + 1 ) );\
	}

#define FUNCTION_GROUP_BASE_IR( T, N )\
	embed T##N T##N##_abs( const T##N v )\
	{\
		out ABS( v );\
	}\
	embed T##N T##N##_sign( const T##N v )\
	{\
		out SIGN( v );\
	}\
	embed T##N T##N##_sign_zero( const T##N v )\
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
	embed r##N r##N##_trunc( const r##N v )\
	{\
		out TRUNC_r( N, v );\
	}\
	embed r##N r##N##_floor( const r##N v )\
	{\
		out FLOOR_r( N, v );\
	}\
	embed r##N r##N##_round( const r##N v )\
	{\
		out ROUND_r( N, v );\
	}\
	embed r##N r##N##_ceil( const r##N v )\
	{\
		out CEIL_r( N, v );\
	}\
	embed r##N r##N##_mod( const r##N v, const r##N m )\
	{\
		out MOD_r( N, v, m );\
	}\
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
	embed r##N r##N##_snap( const r##N v, const r##N multiples_of )\
	{\
		out SNAP_r( N, v, multiples_of );\
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
	embed r##N r##N##_smooth( const r##N v )\
	{\
		out SMOOTH( v );\
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
#define r4_sqrt sqrtf
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
#define r8_sqrt sqrt
#define r8_sin sin
#define r8_cos cos
#define r8_tan tan
#define r8_asin asin
#define r8_acos acos
#define r8_atan atan
#define r8_atanyx atan2

///////

#define KB( KILOBYTES ) ( ( KILOBYTES ) * 1000 )
#define MB( MEGABYTES ) ( ( MEGABYTES ) * 1000000 )
#define GB( GIGABYTES ) ( ( GIGABYTES ) * 1000000000 )

#define KiB( KIBIBYTES ) ( ( KIBIBYTES ) << 10 )
#define MiB( MEBIBYTES ) ( ( MEBIBYTES ) << 20 )
#define GiB( GIBIBYTES ) ( ( GIBIBYTES ) << 30 )

///////

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

///////

#define LZSS_SECTION 4096
#define LZSS_LOOKAHEAD 17
#define LZSS_MIN_MATCH 2

embed n8 bytes_compress( const byte const_ref in_bytes, const n8 bytes_size, byte const_ref out_bytes )
{
	temp const byte ref in_ref = in_bytes;
	temp const byte const_ref in_end = in_ref + bytes_size;
	temp byte ref flag_ref = out_bytes;
	temp byte ref out_ref = flag_ref + 1;
	temp byte flags = 0;
	temp byte flag_bit = 0;

	while( in_ref < in_end )
	{
		temp const byte ref best = 0;
		temp const byte ref scan = 0;
		temp const byte ref section = in_ref - LZSS_SECTION;
		temp const n8 max_length = n4_min( in_end - in_ref, LZSS_LOOKAHEAD );
		temp n1 best_length = 0;

		if( section < in_bytes )
		{
			section = in_bytes;
		}

		scan = section;
		while( scan < in_ref )
		{
			temp n1 length = 0;
			while( length < max_length and scan[ length ] is in_ref[ length ] )
			{
				++length;
			}
			//
			if( length >= LZSS_MIN_MATCH and ( length > best_length or ( length is best_length and in_ref - scan < in_ref - best ) ) )
			{
				best_length = length;
				best = scan;
			}
			++scan;
		}

		if( best_length >= LZSS_MIN_MATCH and best_length < LZSS_LOOKAHEAD and in_ref + 1 < in_end )
		{
			temp n1 next_length = 0;
			temp const n8 next_max = n8_min( in_end - in_ref - 1, LZSS_LOOKAHEAD );

			scan = section;
			while( scan <= in_ref )
			{
				temp n1 length = 0;
				while( length < next_max and scan[ length ] is in_ref[ length + 1 ] )
				{
					++length;
				}
				//
				if( length > next_length )
				{
					next_length = length;
				}
				++scan;
			}

			if( next_length > best_length + 1 )
			{
				val_of( out_ref++ ) = val_of( in_ref++ );
				jump update_flags;
			}
		}

		if( best_length >= LZSS_MIN_MATCH )
		{
			temp const n4 offset = in_ref - best - 1;
			flags |= 1 << flag_bit;
			val_of( out_ref++ ) = offset;
			val_of( out_ref++ ) = ( ( offset >> 8 ) & 0xf ) | ( ( best_length - LZSS_MIN_MATCH ) << 4 );
			in_ref += best_length;
		}
		else
		{
			val_of( out_ref++ ) = val_of( in_ref++ );
		}

		update_flags:
		{
			if( ++flag_bit is 8 )
			{
				val_of( flag_ref ) = flags;
				flags = 0;
				flag_bit = 0;
				flag_ref = out_ref++;
			}
		}
	}

	if( flag_bit isnt 0 )
	{
		val_of( flag_ref ) = flags;
		out out_ref - out_bytes;
	}
	else
	{
		out out_ref - out_bytes - 1;
	}
}

embed n8 bytes_uncompress( const byte const_ref in_bytes, const n2 bytes_size, byte const_ref out_bytes )
{
	temp const byte ref in_ref = in_bytes;
	temp const byte const_ref in_end = in_ref + bytes_size;
	temp byte ref out_ref = out_bytes;

	while( in_ref < in_end )
	{
		temp const n1 flags = val_of( in_ref++ );
		temp n1 bit = 0;

		while( bit < 8 and in_ref < in_end )
		{
			if( flags & ( 1 << bit++ ) )
			{
				skip_if( in_ref + 1 >= in_end );
				temp n1 length = ( n1( in_ref[ 1 ] ) >> 4 ) + LZSS_MIN_MATCH;
				temp const byte ref in_copy = out_ref - ( n1( val_of( in_ref ) ) | ( ( in_ref[ 1 ] & 0xf ) << 8 ) ) - 1;
				in_ref += 2;
				while( length-- )
				{
					val_of( out_ref++ ) = val_of( in_copy++ );
				}
			}
			else
			{
				val_of( out_ref++ ) = val_of( in_ref++ );
			}
		}
	}

	out out_ref - out_bytes;
}

///////

#define format_reset "\033[0m"
//
#define format_bold "\033[1m"
#define format_dim "\033[2m"
#define format_italic "\033[3m"
#define format_underline "\033[4m"
#define format_blink "\033[5m"
#define format_reverse "\033[7m"
#define format_hidden "\033[8m"
#define format_strikethrough "\033[9m"
//
#define format_no_bold "\033[22m"
#define format_no_italic "\033[23m"
#define format_no_underline "\033[24m"
#define format_no_blink "\033[25m"
#define format_no_reverse "\033[27m"
#define format_no_hidden "\033[28m"
#define format_no_strikethrough "\033[29m"
//
#define format_rgb( R, G, B ) "\033[38;2;" #R ";" #G ";" #B "m"
//
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
//
#define format_bg_rgb( R, G, B ) "\033[48;2;" #R ";" #G ";" #B "m"
//
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

//

#define print_set_format( FORMAT ) print_size( format_##FORMAT, size_of( format_##FORMAT ) )
//
#define print_set_rgb( R, G, B ) print( format_rgb( R, G, B ) )
#define print_set_color( COLOR ) print_set_format( COLOR )
#define print_set_dark_color( COLOR ) print_set_format( dark_##COLOR )
#define print_unset_color() print_set_format( color_default )
#define print_set_bg_rgb( R, G, B ) print( format_bg_rgb( R, G, B ) )
#define print_set_bg_color( COLOR ) print_set_format( bg_##COLOR )
#define print_set_bg_dark_color( COLOR ) print_set_format( bg_dark_##COLOR )
#define print_unset_bg_color() print_set_format( bg_default )
//
#define print_set_bold() print_set_format( bold )
#define print_set_dim() print_set_format( dim )
#define print_set_italic() print_set_format( italic )
#define print_set_underline() print_set_format( underline )
#define print_set_blink() print_set_format( blink )
#define print_set_reverse() print_set_format( reverse )
#define print_set_hidden() print_set_format( hidden )
#define print_set_strikethrough() print_set_format( strikethrough )
//
#define print_unset_bold() print_set_format( no_bold )
#define print_unset_italic() print_set_format( no_italic )
#define print_unset_underline() print_set_format( no_underline )
#define print_unset_blink() print_set_format( no_blink )
#define print_unset_reverse() print_set_format( no_reverse )
#define print_unset_hidden() print_set_format( no_hidden )
#define print_unset_strikethrough() print_set_format( no_strikethrough )
//
#define print_reset_format() print_set_format( reset )

#define print_clear() system( PICK( OS_WINDOWS, "cls", "clear" ) )

//

embed const byte const_ref get_print_input()
{
	perm byte print_input[ KB( 1 ) ];
	fgets( print_input, size_of_bytes( print_input ), stdin );
	temp const n2 input_size = bytes_measure( print_input ) - 1;
	print_input[ input_size ] = '\0';
	out print_input;
}

///////

#define is_letter( BYTE ) ( ( ( n4( BYTE ) | 0x20 ) - 'a' ) < 26 )
#define is_number( BYTE ) ( ( n4( BYTE ) - '0' ) < 10 )

///////

#define _BYTES_ADD_BUFFER( BYTES )\
	byte buffer[ BYTES ];\
	byte ref p = buffer + BYTES

#define _BYTES_ADD_NEGATIVE( DST, VAL )\
	if( VAL < 0 )\
	{\
		VAL = -VAL;\
		bytes_add( DST, '-' );\
	}

#define _BYTES_ADD_N( DST, VAL )\
	START_DEF\
	{\
		temp n1 size = 0;\
		do\
		{\
			val_of( --p ) = ( VAL % 10 ) + '0';\
			VAL /= 10;\
			++size;\
		}\
		while( VAL > 0 );\
		bytes_add_bytes( DST, p, size );\
	}\
	END_DEF

#define _BYTES_ADD_I( DST, VAL )\
	START_DEF\
	{\
		_BYTES_ADD_NEGATIVE( DST, VAL );\
		_BYTES_ADD_N( DST, VAL );\
	}\
	END_DEF

#define bytes_add_n1( DST, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 3 );\
		_BYTES_ADD_N( DST, _val );\
	}\
	END_DEF

#define bytes_add_n2( DST, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 5 );\
		_BYTES_ADD_N( DST, _val );\
	}\
	END_DEF

#define bytes_add_n4( DST, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 10 );\
		_BYTES_ADD_N( DST, _val );\
	}\
	END_DEF

#define bytes_add_n8( DST, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 20 );\
		_BYTES_ADD_N( DST, _val );\
	}\
	END_DEF

#define bytes_add_i1( DST, VAL )\
	START_DEF\
	{\
		temp i1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 4 );\
		_BYTES_ADD_I( DST, _val );\
	}\
	END_DEF

#define bytes_add_i2( DST, VAL )\
	START_DEF\
	{\
		temp i2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 6 );\
		_BYTES_ADD_I( DST, _val );\
	}\
	END_DEF

#define bytes_add_i4( DST, VAL )\
	START_DEF\
	{\
		temp i4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 11 );\
		_BYTES_ADD_I( DST, _val );\
	}\
	END_DEF

#define bytes_add_i8( DST, VAL )\
	START_DEF\
	{\
		temp i8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 21 );\
		_BYTES_ADD_I( DST, _val );\
	}\
	END_DEF

#define _BYTES_ADD_R( DST, VAL, N )\
	START_DEF\
	{\
		temp i##N int_part = to( i##N, VAL );\
		temp r##N frac_part = VAL - int_part;\
		_BYTES_ADD_N( DST, int_part );\
		bytes_add( DST, '.' );\
		iter( i, N )\
		{\
			frac_part *= 10;\
			temp const n1 digit = ( n1 ) frac_part;\
			bytes_add( DST, '0' + digit );\
			frac_part -= digit;\
		}\
	}\
	END_DEF

#define bytes_add_r4( DST, VAL )\
	START_DEF\
	{\
		temp r4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 32 );\
		_BYTES_ADD_NEGATIVE( DST, _val );\
		_BYTES_ADD_R( DST, _val, 4 );\
	}\
	END_DEF

#define bytes_add_r8( DST, VAL )\
	START_DEF\
	{\
		temp r8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 64 );\
		_BYTES_ADD_NEGATIVE( DST, _val );\
		_BYTES_ADD_R( DST, _val, 8 );\
	}\
	END_DEF

#define _BYTES_ADD_OCTAL( DST, VAL )\
	START_DEF\
	{\
		temp n1 size = 0;\
		do\
		{\
			* --p = ( VAL & 7 ) + '0';\
			VAL >>= 3;\
			++size;\
		}\
		while( VAL > 0 );\
		bytes_add_bytes( DST, p, size );\
	}\
	END_DEF

#define bytes_add_octal_n1( DST, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 3 );\
		_BYTES_ADD_OCTAL( DST, _val );\
	}\
	END_DEF

#define bytes_add_octal_n2( DST, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 6 );\
		_BYTES_ADD_OCTAL( DST, _val );\
	}\
	END_DEF

#define bytes_add_octal_n4( DST, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 11 );\
		_BYTES_ADD_OCTAL( DST, _val );\
	}\
	END_DEF

#define bytes_add_octal_n8( DST, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 22 );\
		_BYTES_ADD_OCTAL( DST, _val );\
	}\
	END_DEF

#define _BYTES_ADD_HEX( DST, VAL )\
	START_DEF\
	{\
		temp n1 size = 0;\
		do\
		{\
			val_of( --p ) = "0123456789ABCDEF"[ VAL & 0xF ];\
			VAL >>= 4;\
			++size;\
		}\
		while( VAL > 0 );\
		bytes_add_bytes( DST, p, size );\
	}\
	END_DEF

#define bytes_add_hex_n1( DST, VAL )\
	START_DEF\
	{\
		temp n1 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 2 );\
		_BYTES_ADD_HEX( DST, _val );\
	}\
	END_DEF

#define bytes_add_hex_n2( DST, VAL )\
	START_DEF\
	{\
		temp n2 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 4 );\
		_BYTES_ADD_HEX( DST, _val );\
	}\
	END_DEF

#define bytes_add_hex_n4( DST, VAL )\
	START_DEF\
	{\
		temp n4 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 8 );\
		_BYTES_ADD_HEX( DST, _val );\
	}\
	END_DEF

#define bytes_add_hex_n8( DST, VAL )\
	START_DEF\
	{\
		temp n8 _val = ( VAL );\
		_BYTES_ADD_BUFFER( 16 );\
		_BYTES_ADD_HEX( DST, _val );\
	}\
	END_DEF

///////

#define assign_move( FROM_REF, TO_REF ) val_of( TO_REF++ ) = val_of( FROM_REF++ )

embed n4 _format_bytes( byte ref out_bytes, const byte ref format_bytes, arg_list args )
{
	temp const byte const_ref temp_out_bytes = out_bytes;
	if_any( out_bytes is nothing, format_bytes is nothing ) out 0;
	//
	temp flag is_bg = no;
	temp flag is_disable = no;
	temp flag is_dark = no;
	check_format:
	{
		with( val_of( format_bytes ) )
		{
			when( '\0' )
			{
				jump format_eof;
			}
			//
			when( '<' )
			{
				check_format_indicator:
				with( val_of( format_bytes + 1 ) )
				{
					when( '\0' )
					{
						jump process_format;
					}
					//
					when( '>' )
					{
						temp const byte const_ref b = to( byte const_ref, args_next( args, ref ) );
						bytes_paste_move( b, out_bytes );
						format_bytes += 2;
						skip;
					}
					//
					when( '/' )
					{
						if( val_of( format_bytes + 2 ) is '>' )
						{
							bytes_paste_move( separator, out_bytes );
							format_bytes += 3;
							skip;
						}
						//
						is_disable = yes;
						++format_bytes;
						jump check_format_indicator;
					}
					//
					when( 'u' )
					{
						if( val_of( format_bytes + 2 ) is '>' )
						{
							bytes_paste_move( pick( is_disable, format_no_underline, format_underline ), out_bytes );
							format_bytes += 3;
							skip;
						}
						else
						{
							jump process_format;
						}
					}
					//
					when( 'i' )
					{
						if( val_of( format_bytes + 2 ) is '>' )
						{
							bytes_paste_move( pick( is_disable, format_no_italic, format_italic ), out_bytes );
							format_bytes += 3;
							skip;
						}
						else
						{
							jump process_format;
						}
					}
					//
					when( 'b' )
					{
						if( val_of( format_bytes + 2 ) is '>' )
						{
							bytes_paste_move( pick( is_disable, format_no_bold, format_bold ), out_bytes );
							format_bytes += 3;
							skip;
						}
						else if( val_of( format_bytes + 2 ) isnt 'g' )
						{
							jump process_format;
						}
						//
						++format_bytes;
						is_bg = yes;
					} // fall through
					when( 'c' )
					{
						if( is_disable )
						{
							if( val_of( format_bytes + 2 ) is '>' )
							{
								bytes_paste_move( pick( is_bg is yes, format_bg_default, format_color_default ), out_bytes );
								format_bytes += 3;
								skip;
							}
						}
						//
						++format_bytes;
						with( val_of( format_bytes + 1 ) )
						{
							when( '\0' )
							{
								jump process_format;
							}
							//
							when( 'o' )
							{
								if( bytes_compare( format_bytes, "olor", 4 ) isnt 0 )
								{
									jump check_format;
								}
								format_bytes += 4;
							} // else fall through
							when( ':' )
							{
								check_format_color:
								++format_bytes;
								with( val_of( format_bytes + 1 ) )
								{
									when( 'd' )
									{
										is_dark = yes;
										goto check_format_color;
									}
									//
									when( 'w' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_gray, format_bg_white ), pick( is_dark is yes, format_gray, format_white ) ), out_bytes );
										skip;
									}
									//
									when( 'r' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_red, format_bg_red ), pick( is_dark is yes, format_dark_red, format_red ) ), out_bytes );
										skip;
									}
									//
									when( 'y' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_yellow, format_bg_yellow ), pick( is_dark is yes, format_dark_yellow, format_yellow ) ), out_bytes );
										skip;
									}
									//
									when( 'g' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_green, format_bg_green ), pick( is_dark is yes, format_dark_green, format_green ) ), out_bytes );
										skip;
									}
									//
									when( 'c' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_cyan, format_bg_cyan ), pick( is_dark is yes, format_dark_cyan, format_cyan ) ), out_bytes );
										skip;
									}
									//
									when( 'b' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_blue, format_bg_blue ), pick( is_dark is yes, format_dark_blue, format_blue ) ), out_bytes );
										skip;
									}
									//
									when( 'm' )
									{
										bytes_paste_move( pick( is_bg is yes, pick( is_dark is yes, format_bg_dark_magenta, format_bg_magenta ), pick( is_dark is yes, format_dark_magenta, format_magenta ) ), out_bytes );
										skip;
									}
								}
								//
								format_bytes += 3;
							}
							//
							other skip;
						}
						is_bg = no;
						is_disable = no;
						is_dark = no;
						skip;
					}
					//
					other
					{
						val_of( out_bytes++ ) = '{';
						goto process_format;
					}
				}
				//
				jump check_format;
			}
			//
			other
			{
				process_format:
				val_of( out_bytes++ ) = val_of( format_bytes++ );
				jump check_format;
			}
		}
	}
	//
	format_eof:
	bytes_end( out_bytes );
	out out_bytes - temp_out_bytes;
}

embed n4 format_bytes( byte const_ref out_bytes, const byte ref format_bytes, ... )
{
	arg_list args;
	args_init( args, format_bytes );
	out _format_bytes( out_bytes, format_bytes, args );
}

#define format_bytes_move( OUT_BYTES, FORMAT_BYTES, ARGS... ) OUT_BYTES += format_bytes( OUT_BYTES, FORMAT_BYTES COMMA_IF_ARGS( ARGS ) ARGS )

///////

fn format_print( const byte const_ref format_bytes, ... )
{
	arg_list args;
	args_init( args, format_bytes );
	perm byte format[ KB( 2 ) ];
	temp byte ref format_ref = format;
	print_size( format, _format_bytes( format_ref, format_bytes, args ) );
}

///////

#define max_path_size 260
#define max_entry_size 65

///////

group( entry_type )
{
	entry_unknown,
	entry_files,
	entry_folders,
	entry_any
};

embed n2 get_entries( const byte const_ref folder_path, byte entries[][ max_path_size ], const n2 max_entries, const entry_type type, const flag folder_separator )
{
	temp n2 count = 0;
	temp n2 len = bytes_measure( folder_path );
	perm byte path[ max_path_size ];
	bytes_clear( path, max_path_size );
	anon ref handle;
	bytes_copy( folder_path, len, path );

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
			bytes_copy( entry->d_name, entry_size, path + len );
			//
			if( stat( path, ref_of( stat_buf ) ) is 0 )
			{
				temp flag is_dir = flag( S_ISDIR( stat_buf.st_mode ) );
				if( type is entry_any or ( type is entry_folders and is_dir is yes ) or ( type is entry_files and is_dir is no ) )
				{
					bytes_copy( entry->d_name, entry_size, entries[ count ] );
					if( is_dir and folder_separator )
					{
						entries[ count ][ entry_size - 1 ] = val_of( separator );
						entries[ count ][ entry_size ] = '\0';
					}
					++count;
				}
			}
		}
		closedir( handle );
	#elif OS_WINDOWS
		WIN32_FIND_DATA entry;
		bytes_copy( "\\*", 3, path + len );
		handle = FindFirstFile( path, ref_of( entry ) );
		if( handle is INVALID_HANDLE_VALUE ) out 0;
		//
		do
		{
			next_if( entry.cFileName[ 0 ] is '.' );
			temp flag is_dir = flag( entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY );
			if( type is entry_any or ( type is entry_folders and is_dir is yes ) or ( type is entry_files and is_dir is no ) )
			{
				temp n2 entry_size = bytes_measure( entry.cFileName ) + 1;
				bytes_copy( entry.cFileName, entry_size, entries[ count++ ] );
				if( is_dir and folder_separator )
				{
					entries[ count ][ entry_size - 1 ] = val_of( separator );
					entries[ count ][ entry_size ] = '\0';
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

///////

fn create_folder( const byte const_ref path )
{
	#if OS_LINUX
		mkdir( path, 0755 );
	#else
		CreateDirectoryA( path, nothing );
	#endif
}

fn delete_folder( const byte const_ref path )
{
	#if OS_LINUX
		rmdir( path );
	#else
		RemoveDirectoryA( path );
	#endif
}

embed flag folder_exists( const byte const_ref path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISDIR( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and ( attrib & FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

embed flag file_exists( const byte const_ref path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISREG( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and not ( attrib & FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

///////

#define path( FOLDERS... ) CHAIN(,, separator, FOLDERS )

fn path_up_folder( byte const_ref path )
{
	temp byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt '\\' and val_of( p ) isnt '/' );
	if( p > path ) val_of( p ) = '\0';
}

embed const byte const_ref path_get_name( const byte const_ref path )
{
	temp const byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt '\\' and val_of( p ) isnt '/' );
	if( p > path ) ++p;
	out p;
}

///////

type_from( FILE ref ) os_file_handle;

type( file )
{
	byte path[ max_path_size ];
	n2 path_size;
	os_file_handle handle;
	byte ref mapped_bytes;
	n8 size;
};

embed n8 get_file_size( const byte const_ref file_path )
{
	#if OS_LINUX
		struct stat st;
		out pick( stat( file_path, ref_of( st ) ) is 0, to( const n8, st.st_size ), 0 );
	#elif OS_WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		out pick( GetFileAttributesExA( file_path, GetFileExInfoStandard, ref_of( fad ) ), to( const n8, ( n8( fad.nFileSizeHigh ) << 32 ) | n8( fad.nFileSizeLow ) ), 0 );
	#endif
}

embed file _open_file_loading( const byte const_ref path, const n4 path_size )
{
	file f = { 0 };
	f.size = get_file_size( path );
	if( f.size is 0 )
	{
		out f;
	}
	//
	f.handle = fopen( path, "rb" );
	if_nothing( f.handle )
	{
		out f;
	}
	//
	f.path_size = path_size;
	bytes_copy( path, f.path_size, f.path );
	//
	out f;
}

embed file _open_file_saving( const byte const_ref path, const n4 path_size )
{
	file f = { 0 };
	f.handle = fopen( path, "wb" );
	if_nothing( f.handle )
	{
		out f;
	}
	//
	f.size = 0;
	f.path_size = path_size;
	bytes_copy( path, f.path_size, f.path );
	//
	out f;
}

#define open_file( PATH, PATH_SIZE... ) _open_file_loading( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )
#define new_file( PATH, PATH_SIZE... ) _open_file_saving( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )

embed file _map_file( const byte const_ref path, const n4 path_size )
{
	file f = { 0 };
	//
	f.size = get_file_size( path );
	if( f.size is 0 )
	{
		out f;
	}
	//
	#if OS_LINUX
		temp i4 fd = open( path, O_RDONLY );
		out_if( fd is -1 ) f;
		//
		temp anon ref mapped_bytes = mmap( nothing, f.size, PROT_READ, MAP_PRIVATE, fd, 0 );
		close( fd );
		out_if( mapped_bytes is MAP_FAILED ) f;
		f.mapped_bytes = to( byte ref, mapped_bytes );
	#elif OS_WINDOWS
		temp HANDLE file = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, nothing, OPEN_EXISTING, 0, nothing );
		out_if( file is INVALID_HANDLE_VALUE ) f;
		//
		temp HANDLE mapping = CreateFileMapping( file, nothing, PAGE_READONLY, 0, 0, nothing );
		CloseHandle( file );
		if_nothing( mapping )
		{
			out f;
		}
		//
		f.mapped_bytes = to( byte ref, MapViewOfFile( mapping, FILE_MAP_READ, 0, 0, 0 ) );
		CloseHandle( mapping );
	#endif
	//
	f.path_size = path_size;
	bytes_copy( path, f.path_size, f.path );
	//
	out f;
}
#define map_file( PATH, PATH_SIZE... ) _map_file( PATH, DEFAULT( bytes_measure( PATH ), PATH_SIZE ) )

//

fn file_load( file ref f, byte const_ref out_bytes )
{
	if_nothing( f->handle ) out;
	//
	fseek( f->handle, 0, SEEK_SET );
	fread( out_bytes, 1, f->size, f->handle );
	i4 y = 2;
	anon ref x = to( anon ref, ref_of( y ) );
}

fn file_save( file ref f, const byte const_ref bytes, const n8 size )
{
	if_nothing( f->handle ) out;
	//
	fseek( f->handle, 0, SEEK_SET );
	f->size = size;
	fwrite( bytes, 1, f->size, f->handle );
	fflush( f->handle );
}

//

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
	//
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
	//
	file_clear( f );
}

fn delete_file( const char const_ref path )
{
	remove( path );
}

///////

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

///////

#define nano_per_micro 1000
#define nano_per_milli 1000000
#define nano_per_sec 1000000000
#define nano_per_min 60000000000
#define nano_per_hour 3600000000000
#define micro_per_milli 1000
#define micro_per_sec 1000000
#define micro_per_min 60000000
#define micro_per_hour 3600000000
#define milli_per_sec 1000
#define milli_per_min 60000
#define milli_per_hour 3600000
#define sec_per_min 60
#define sec_per_hour 3600
#define min_per_hour 60

type_from( n8 ) nano;

embed nano _get_nano()
{
	#if OS_WINDOWS
		perm LARGE_INTEGER frequency;
		perm LARGE_INTEGER start;
		LARGE_INTEGER current;

		once
		{
			QueryPerformanceFrequency( ref_of( frequency ) );
			QueryPerformanceCounter( ref_of( start ) );
		}

		QueryPerformanceCounter( ref_of( current ) );

		out( ( current.QuadPart - start.QuadPart ) * 1000000000ULL ) / frequency.QuadPart;
	#else
		struct timespec ts;
		clock_gettime( CLOCK_MONOTONIC, ref_of( ts ) );
		out to( nano, ts.tv_sec * nano_per_sec + ts.tv_nsec );
	#endif
}

embed nano get_nano()
{
	perm nano epoch = 0;
	once
	{
		epoch = _get_nano();
	}
	out _get_nano() - epoch;
}

fn nano_sleep( const nano time )
{
	#if OS_WINDOWS
		LARGE_INTEGER freq,
		start,
		now;
		QueryPerformanceFrequency( ref_of( freq ) );
		QueryPerformanceCounter( ref_of( start ) );

		static HANDLE timer = nothing;
		once timer = CreateWaitableTimer( nothing, TRUE, nothing );

		LARGE_INTEGER li = { .QuadPart = -( time / 100 ) };
		SetWaitableTimer( timer, ref_of( li ), 0, nothing, nothing, FALSE );
		WaitForSingleObject( timer, INFINITE );

		n8 target = start.QuadPart + ( time * freq.QuadPart ) / nano_per_sec;
		while( QueryPerformanceCounter( ref_of( now ) ), now.QuadPart < target );
	#else
		struct timespec ts = { time / nano_per_sec, time mod nano_per_sec };
		nanosleep( ref_of( ts ), nothing );
	#endif
}

///////

#define DECLARE_TYPE_2D( TYPE )\
	fusion( TYPE##x2 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
		};\
		variant\
		{\
			TYPE w;\
			TYPE h;\
		};\
	}

#define DECLARE_TYPE_3D( TYPE )\
	fusion( TYPE##x3 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
			TYPE z;\
		};\
		variant\
		{\
			TYPE w;\
			TYPE h;\
			TYPE d;\
		};\
	}

#define DECLARE_TYPE_4D( TYPE )\
	fusion( TYPE##x4 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
			TYPE z;\
			TYPE w;\
		};\
		variant\
		{\
			TYPE r;\
			TYPE g;\
			TYPE b;\
			TYPE a;\
		};\
	}

#define DECLARE_TYPE_2D_FN( TYPE )\
	embed TYPE##x2 TYPE##x2_invert( const TYPE##x2 X )\
	{\
		out make( TYPE##x2, .x = -X.x, .y = -X.y );\
	}\
	embed TYPE##x2 TYPE##x2_add( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x + B.x, .y = A.y + B.y );\
	}\
	embed TYPE##x2 TYPE##x2_add_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x + V, .y = A.y + V );\
	}\
	embed TYPE##x2 TYPE##x2_sub( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x - B.x, .y = A.y - B.y );\
	}\
	embed TYPE##x2 TYPE##x2_sub_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x - V, .y = A.y - V );\
	}\
	embed TYPE##x2 TYPE##x2_mul( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x * B.x, .y = A.y * B.y );\
	}\
	embed TYPE##x2 TYPE##x2_mul_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x * V, .y = A.y * V );\
	}\
	embed TYPE##x2 TYPE##x2_div( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x / B.x, .y = A.y / B.y );\
	}\
	embed TYPE##x2 TYPE##x2_div_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x / V, .y = A.y / V );\
	}\
	embed TYPE TYPE##x2_dot( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out A.x * B.x + A.y * B.y;\
	}\
	embed TYPE TYPE##x2_mag_sqr( const TYPE##x2 A )\
	{\
		out TYPE##x2_dot( A, A );\
	}\
	embed TYPE TYPE##x2_distance_sqr( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out TYPE##x2_mag_sqr( TYPE##x2_sub( B, A ) );\
	}

#define DECLARE_TYPE_3D_FN( TYPE )\
	embed TYPE##x3 TYPE##x3_invert( const TYPE##x3 X )\
	{\
		out make( TYPE##x3, .x = -X.x, .y = -X.y, .z = -X.z );\
	}\
	embed TYPE##x3 TYPE##x3_add( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z );\
	}\
	embed TYPE##x3 TYPE##x3_add_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x + V, .y = A.y + V, .z = A.z + V );\
	}\
	embed TYPE##x3 TYPE##x3_sub( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z );\
	}\
	embed TYPE##x3 TYPE##x3_sub_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x - V, .y = A.y - V, .z = A.z - V );\
	}\
	embed TYPE##x3 TYPE##x3_mul( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z );\
	}\
	embed TYPE##x3 TYPE##x3_mul_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x * V, .y = A.y * V, .z = A.z * V );\
	}\
	embed TYPE##x3 TYPE##x3_div( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z );\
	}\
	embed TYPE##x3 TYPE##x3_div_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x / V, .y = A.y / V, .z = A.z / V );\
	}\
	embed TYPE TYPE##x3_dot( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z;\
	}\
	embed TYPE TYPE##x3_mag_sqr( const TYPE##x3 A )\
	{\
		out TYPE##x3_dot( A, A );\
	}\
	embed TYPE TYPE##x3_distance_sqr( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out TYPE##x3_mag_sqr( TYPE##x3_sub( B, A ) );\
	}\
	embed TYPE##x3 TYPE##x3_cross( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.y * B.z - A.z * B.y, .y = A.z * B.x - A.x * B.z, .z = A.x * B.y - A.y * B.x );\
	}

#define DECLARE_TYPE_4D_FN( TYPE )\
	embed TYPE##x4 TYPE##x4_invert( const TYPE##x4 X )\
	{\
		out make( TYPE##x4, .x = -X.x, .y = -X.y, .z = -X.z, .w = -X.w );\
	}\
	embed TYPE##x4 TYPE##x4_add( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z, .w = A.w + B.w );\
	}\
	embed TYPE##x4 TYPE##x4_add_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x + V, .y = A.y + V, .z = A.z + V, .w = A.w + V );\
	}\
	embed TYPE##x4 TYPE##x4_sub( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z, .w = A.w - B.w );\
	}\
	embed TYPE##x4 TYPE##x4_sub_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x - V, .y = A.y - V, .z = A.z - V, .w = A.w - V );\
	}\
	embed TYPE##x4 TYPE##x4_mul( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z, .w = A.w * B.w );\
	}\
	embed TYPE##x4 TYPE##x4_mul_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x * V, .y = A.y * V, .z = A.z * V, .w = A.w * V );\
	}\
	embed TYPE##x4 TYPE##x4_div( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z, .w = A.w / B.w );\
	}\
	embed TYPE##x4 TYPE##x4_div_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x / V, .y = A.y / V, .z = A.z / V, .w = A.w / V );\
	}\
	embed TYPE TYPE##x4_dot( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;\
	}\
	embed TYPE TYPE##x4_mag_sqr( const TYPE##x4 A )\
	{\
		out TYPE##x4_dot( A, A );\
	}\
	embed TYPE TYPE##x4_distance_sqr( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out TYPE##x4_mag_sqr( TYPE##x4_sub( B, A ) );\
	}

#define DECLARE_TYPE_XD_FN_R( N, X )\
	embed r##N r##N##x##X##_mag( const r##N##x##X A )\
	{\
		out r##N##_sqrt( r##N##x##X##_mag_sqr( A ) );\
	}\
	embed r##N r##N##x##X##_distance( const r##N##x##X A, const r##N##x##X B )\
	{\
		out r##N##_sqrt( r##N##x##X##_distance_sqr( A, B ) );\
	}\
	embed r##N##x##X r##N##x##X##_norm( const r##N##x##X A )\
	{\
		out r##N##x##X##_mul_##r##N( A, 1.0 / r##N##x##X##_mag( A ) );\
	}

//

#define DECLARE_TYPE_MULTI( TYPE )\
	DECLARE_TYPE_2D( TYPE );\
	DECLARE_TYPE_3D( TYPE );\
	DECLARE_TYPE_4D( TYPE );\
	DECLARE_TYPE_2D_FN( TYPE );\
	DECLARE_TYPE_3D_FN( TYPE );\
	DECLARE_TYPE_4D_FN( TYPE )

#define DECLARE_TYPE_MULTI_R( N )\
	DECLARE_TYPE_XD_FN_R( N, 2 );\
	DECLARE_TYPE_XD_FN_R( N, 3 );\
	DECLARE_TYPE_XD_FN_R( N, 4 )

//

DECLARE_TYPE_MULTI( n1 );
DECLARE_TYPE_MULTI( i1 );
DECLARE_TYPE_MULTI( n2 );
DECLARE_TYPE_MULTI( i2 );
DECLARE_TYPE_MULTI( n4 );
DECLARE_TYPE_MULTI( i4 );
DECLARE_TYPE_MULTI( r4 );
DECLARE_TYPE_MULTI_R( 4 );
DECLARE_TYPE_MULTI( n8 );
DECLARE_TYPE_MULTI( i8 );
DECLARE_TYPE_MULTI( r8 );
DECLARE_TYPE_MULTI_R( 8 );

#define x2_area( x2 ) ( x2.w * x2.h )

//

#define point_in_size( X, Y, W, H ) all( X >= 0, Y >= 0, X < W, Y < H )
#define point_not_in_size( X, Y, W, H ) any( X < 0, Y < 0, X >= W, Y >= H )

#define point_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) all( X >= TOPLEFT_X, Y >= TOPLEFT_Y, X <= BOTTOMRIGHT_X, Y <= BOTTOMRIGHT_Y )
#define point_not_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) any( X < TOPLEFT_X, Y < TOPLEFT_Y, X > BOTTOMRIGHT_X, Y > BOTTOMRIGHT_Y )

#define box_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) all( point_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )
#define box_not_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) any( point_not_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_not_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )

#define box_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) all( point_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )
#define box_not_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) any( point_not_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_not_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )

///////

type_from( r4x2 ) vec2;
#define _vec2( X, Y ) make( r4x2, .x = X, .y = Y )
#define _eval_vec2( X_Y... ) _vec2( X_Y )
#define vec2( X_Y... ) _eval_vec2( DEFAULTS( ( 0.0, 0.0 ), X_Y ) )

#define vec2_invert r4x2_invert
#define vec2_add r4x2_add
#define vec2_add_r4 r4x2_add_r4
#define vec2_sub r4x2_sub
#define vec2_sub_r4 r4x2_sub_r4
#define vec2_mul r4x2_mul
#define vec2_mul_r4 r4x2_mul_r4
#define vec2_div r4x2_div
#define vec2_div_r4 r4x2_div_r4
#define vec2_dot r4x2_dot
#define vec2_norm r4x2_norm
#define vec2_distance r4x2_distance

type( spinor )
{
	r4 r;
	r4 i;
};

#define spinor( R, I ) make( spinor, .r = R, .i = I )
#define spinor_default() spinor( 1.0, 0.0 )

embed spinor new_spinor( const r4 angle )
{
	out spinor( r4_cos( angle ), r4_sin( angle ) );
}

embed spinor invert_spinor( const spinor s )
{
	out spinor( s.r, -s.i );
}

embed spinor spinor_add( const spinor a, const spinor b )
{
	out spinor( a.r + b.r, a.i + b.i );
}

embed spinor spinor_sub( const spinor a, const spinor b )
{
	out spinor( a.r - b.r, a.i - b.i );
}

embed spinor spinor_mul_r4( const spinor s, const r4 f )
{
	out spinor( s.r * f, s.i * f );
}

#define spinor_halve( S ) spinor_mul_r4( S, 0.5 )

embed spinor spinor_mul( const spinor a, const spinor b )
{
	out spinor( a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r );
}

embed vec2 vec2_rotate( const vec2 v, const spinor s )
{
	temp const r4 cos2 = s.r * s.r - s.i * s.i;
	temp const r4 sin2 = 2.0 * s.r * s.i;
	out vec2( cos2 * v.x - sin2 * v.y, sin2 * v.x + cos2 * v.y );
}

type( planor )
{
	spinor s;
	spinor t;
};

#define planor( S, T ) make( planor, .s = S, .t = T )
#define planor_default() planor( spinor_default(), spinor( 0.0, 0.0 ) )

embed planor new_planor( const spinor s, const vec2 pos )
{
	out planor( s, spinor_halve( spinor_mul( spinor( pos.x, pos.y ), s ) ) );
}

embed vec2 planor_get_vec2( const planor p )
{
	out vec2( 2.0 * ( p.t.r * p.s.r + p.t.i * p.s.i ), 2.0 * ( p.t.i * p.s.r - p.t.r * p.s.i ) );
}

embed planor invert_planor( const planor p )
{
	temp const spinor inv_s = invert_spinor( p.s );
	temp const spinor inv_t = spinor_mul( spinor_mul( inv_s, p.t ), inv_s );
	out planor( inv_s, spinor( -inv_t.r, -inv_t.i ) );
}

embed planor planor_mul( const planor a, const planor b )
{
	out planor( spinor_mul( a.s, b.s ), spinor_add( spinor_mul( a.s, b.t ), spinor_mul( a.t, b.s ) ) );
}

embed planor planor_set_rotation( const planor p, const spinor new_s )
{
	out planor( new_s, spinor_halve( spinor_mul( spinor_mul( spinor_mul_r4( p.t, 2.0 ), invert_spinor( p.s ) ), new_s ) ) );
}

embed planor planor_add_spinor( const planor p, const spinor s )
{
	out planor_set_rotation( p, spinor_mul( p.s, s ) );
}

embed planor planor_add_vec2( const planor p, const vec2 delta )
{
	out planor( p.s, spinor_add( p.t, spinor_mul( spinor_halve( spinor( delta.x, delta.y ) ), p.s ) ) );
}

embed planor planor_translate( const planor p, const vec2 delta )
{
	temp const vec2 world_delta = vec2_rotate( delta, p.s );
	out planor_add_vec2( p, world_delta );
}

embed vec2 vec2_transform( const vec2 v, const planor p )
{
	temp const r4 cos2 = p.s.r * p.s.r - p.s.i * p.s.i;
	temp const r4 sin2 = 2.0 * p.s.r * p.s.i;
	out vec2( cos2 * v.x - sin2 * v.y + ( 2.0 * ( p.t.r * p.s.r + p.t.i * p.s.i ) ), sin2 * v.x + cos2 * v.y + ( 2.0 * ( p.t.i * p.s.r - p.t.r * p.s.i ) ) );
}

///////

type_from( r4x3 ) vec3;
#define _vec3( X, Y, Z ) make( r4x3, .x = X, .y = Y, .z = Z )
#define _eval_vec3( X_Y_Z... ) _vec3( X_Y_Z )
#define vec3( X_Y_Z... ) _eval_vec3( DEFAULTS( ( 0.0, 0.0, 0.0 ), X_Y_Z ) )

#define vec3_invert r4x3_invert
#define vec3_add r4x3_add
#define vec3_add_r4 r4x3_add_r4
#define vec3_sub r4x3_sub
#define vec3_sub_r4 r4x3_sub_r4
#define vec3_mul r4x3_mul
#define vec3_mul_r4 r4x3_mul_r4
#define vec3_div r4x3_div
#define vec3_div_r4 r4x3_div_r4
#define vec3_dot r4x3_dot
#define vec3_cross r4x3_cross
#define vec3_norm r4x3_norm

type_from( r4 ) hangle;

type( rotor )
{
	vec3 v;
	hangle h;
};

#define rotor( V, H ) make( rotor, .v = V, .h = H )
#define rotor_default() rotor( vec3( 0.0 ), 1.0 )

embed rotor new_rotor( const vec3 norm_v, const hangle h )
{
	out rotor( vec3_mul_r4( norm_v, r4_sin( h ) ), r4_cos( h ) );
}

//

embed rotor yaw_rotor( const hangle h ) // Z AXIS
{
	out rotor( vec3( 0., 0., sin( h ) ), cos( h ) );
}

embed rotor pitch_rotor( const hangle h ) // Y AXIS
{
	out rotor( vec3( 0., sin( h ), 0. ), cos( h ) );
}

embed rotor roll_rotor( const hangle h ) // X AXIS
{
	out rotor( vec3( sin( h ), 0., 0. ), cos( h ) );
}

//

embed rotor invert_rotor( const rotor r )
{
	out rotor( vec3_invert( r.v ), r.h );
}

//

embed rotor rotor_add( const rotor a, const rotor b )
{
	out rotor( vec3_add( a.v, b.v ), a.h + b.h );
}

embed rotor rotor_sub( const rotor a, const rotor b )
{
	out rotor( vec3_sub( a.v, b.v ), a.h - b.h );
}

embed rotor rotor_mul_r4( const rotor r, const r4 f )
{
	out rotor( vec3_mul_r4( r.v, f ), r.h * f );
}

#define rotor_halve( R ) rotor_mul_r4( R, 0.5 )

embed rotor rotor_mul( const rotor a, const rotor b )
{
	temp const r4 i = ( a.v.z + a.v.x ) * ( b.v.x + b.v.y );
	temp const r4 j = ( a.h + a.v.y ) * ( b.h - b.v.z );
	temp const r4 k = ( a.h - a.v.y ) * ( b.h + b.v.z );
	temp const r4 l = i + j + k;
	temp const r4 m = 0.5 * ( ( a.v.z - a.v.x ) * ( b.v.x - b.v.y ) + l );
	out rotor( vec3( ( a.h + a.v.x ) * ( b.h + b.v.x ) + m - l, ( a.h - a.v.x ) * ( b.v.y + b.v.z ) + m - k, ( a.v.y + a.v.z ) * ( b.h - b.v.x ) + m - j ), ( a.v.z - a.v.y ) * ( b.v.y - b.v.z ) + m - i );

	//out rotor( vec3_add( vec3_add( vec3_mul_r4( b.v, a.h ), vec3_mul_r4( a.v, b.h ) ), vec3_cross( a.v, b.v ) ), ( a.h * b.h ) - vec3_dot( a.v, b.v ) );
}

//

embed rotor construct_rotor( const hangle yaw, const hangle pitch, const hangle roll )
{
	temp const r4 sy = r4_sin( yaw );
	temp const r4 cy = r4_cos( yaw );
	temp const r4 sp = r4_sin( pitch );
	temp const r4 cp = r4_cos( pitch );
	temp const r4 sr = r4_sin( roll );
	temp const r4 cr = r4_cos( roll );
	out rotor( vec3( sr * cp * cy - cr * sp * sy, cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy ), cr * cp * cy + sr * sp * sy );

	//out rotor_mul( rotor_mul( yaw_rotor( yaw ), pitch_rotor( pitch ) ), roll_rotor( roll ) );
}

//

embed rotor look_rotor( const vec3 from_v, const vec3 to_v, const hangle roll )
{
	temp const vec3 dir = vec3_norm( vec3_sub( to_v, from_v ) );
	out construct_rotor( r4_atanyx( dir.y, dir.x ) * 0.5, r4_asin( -dir.z ) * 0.5, roll );
}

//

embed vec3 vec3_rotate( const vec3 v, const rotor r )
{
	temp const r4 a = r.v.y * v.z - r.v.z * v.y;
	temp const r4 b = r.v.z * v.x - r.v.x * v.z;
	temp const r4 c = r.v.x * v.y - r.v.y * v.x;
	out vec3( v.x + 2.0 * ( r.h * a + r.v.y * c - r.v.z * b ), v.y + 2.0 * ( r.h * b + r.v.z * a - r.v.x * c ), v.z + 2.0 * ( r.h * c + r.v.x * b - r.v.y * a ) );

	//temp const vec3 c = vec3_mul_r4( vec3_cross( r.v, v ), 2.0 );
	//out vec3_sub( vec3_add( v, vec3_mul_r4( c, r.h ) ), vec3_cross( c, r.v ) );
}

///////

type( motor )
{
	rotor r;
	rotor t;
};

#define motor( R, T ) make( motor, .r = R, .t = T )

embed motor new_motor( const rotor r, const vec3 pos )
{
	out motor( r, rotor_halve( rotor_mul( rotor( vec3( pos.x, pos.y, pos.z ), 0. ), r ) ) );
}

embed motor invert_motor( const motor m )
{
	out motor( invert_rotor( m.r ), invert_rotor( m.t ) );
}

embed motor motor_mul( const motor a, const motor b )
{
	out motor( rotor_mul( a.r, b.r ), rotor_add( rotor_mul( a.r, b.t ), rotor_mul( a.t, b.r ) ) );
}

embed vec3 vec3_transform( const vec3 v, const motor m )
{
	out motor_mul( motor_mul( m, motor( rotor_default(), rotor( v, 0.0 ) ) ), motor( rotor( vec3_invert( m.r.v ), m.r.h ), rotor( m.t.v, -m.t.h ) ) ).t.v;
}

///////

type( projection )
{
	r4 view_scale;
};

#define projection( VIEW_SCALE ) make( projection, .view_scale = VIEW_SCALE )

embed projection new_projection( const float fov_degrees )
{
	out projection( 1.0 / r4_tan( fov_degrees * 0.5 ) );
}

embed vec3 world_to_view( const vec3 v )
{
	out vec3( -v.y, -v.z, v.x );
}

embed vec3 view_to_world( vec3 v )
{
	//v.y = -v.y;
	out vec3( v.z, -v.x, -v.y );
}

embed vec3 vec3_project( const vec3 world_v, const projection p )
{
	vec3 pos = world_to_view( world_v );
	//pos.y = -pos.y;
	float z = pos.z;

	out vec3( pos.x / z * p.view_scale, pos.y / z * p.view_scale, 1.0 / z );
}

///////

type_from( motor ) observer;

embed observer new_observer( const vec3 from_v, const vec3 to_v, const hangle roll )
{
	out invert_motor( new_motor( look_rotor( from_v, to_v, roll ), from_v ) );
}

embed vec3 vec3_observe( const vec3 world_v, const observer o, const projection p )
{
	out vec3_project( vec3_transform( world_v, o ), p );
}

///////

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

///////

#define _main_fn out_state main( const i4 parameters_count, const byte const_ref const_ref parameters )
#define start _main_fn

/////// /////// /////// /////// /////// /////// ////////
