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
	#define _GNU_SOURCE
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <dirent.h>
	#include <fcntl.h>
	#include <unistd.h>
	#define SEPARATOR "/"
	#ifdef C7H16
		#include <X11/Xlib.h>
		#include <X11/Xutil.h>
		#include <X11/extensions/Xrender.h>
	#endif
	//
#elif defined( _WIN32 )
	#undef OS_WINDOWS
	#define OS_WINDOWS 1
	#define OS_NAME "Windows"
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>
	#define SEPARATOR "\\"
	//
#elif defined( __APPLE__ )
	#undef OS_MACOS
	#define OS_MACOS 1
	#define OS_NAME "macOS"
	//
#else
	#undef OS_UNKNOWN
	#define OS_UNKNOWN 1
	#define OS_NAME "unknown"
#endif

///////

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define _CHAIN_0( L, R, MID, ARGS... ) ARGS
#define _CHAIN_1( L, R, MID, ARG ) L ARG R
#define _CHAIN_JOIN( L, R, MID, ARG, NEXT ) _CHAIN_1( L, R, MID, ARG ) MID NEXT
#define _CHAIN_2( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_1( L, R, MID, ARGS ) )
#define _CHAIN_3( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_2( L, R, MID, ARGS ) )
#define _CHAIN_4( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_3( L, R, MID, ARGS ) )
#define _CHAIN_5( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_4( L, R, MID, ARGS ) )
#define _CHAIN_6( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_5( L, R, MID, ARGS ) )
#define _CHAIN_7( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_6( L, R, MID, ARGS ) )
#define _CHAIN_8( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_7( L, R, MID, ARGS ) )
#define _CHAIN_9( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_8( L, R, MID, ARGS ) )
#define _CHAIN_10( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_9( L, R, MID, ARGS ) )
#define _CHAIN_11( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_10( L, R, MID, ARGS ) )
#define _CHAIN_12( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_11( L, R, MID, ARGS ) )
#define _CHAIN_13( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_12( L, R, MID, ARGS ) )
#define _CHAIN_14( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_13( L, R, MID, ARGS ) )
#define _CHAIN_15( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_14( L, R, MID, ARGS ) )
#define _CHAIN_16( L, R, MID, ARG, ARGS... ) _CHAIN_JOIN( L, R, MID, ARG, _CHAIN_15( L, R, MID, ARGS ) )
#define _CHAIN_MAKE( COUNT, L, R, MID, ARGS... ) JOIN( _CHAIN_, COUNT ) ( L, R, MID, ARGS )
#define CHAIN( L, R, MID, ARGS... ) _CHAIN_MAKE( COUNT_ARGS( ARGS ), L, R, MID, ARGS )

///////

#define AS_BYTES( VALUE ) #VALUE

///////

#define ref *
#define const_ref ref const
#define temp register
#define perm static
#define global /*explicitly global*/

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
#define flip( FLAG ) FLAG = not FLAG
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

#define _range_step( POS_NAME, FROM, TO, STEP, SYMBOL, COUNTER )\
	for( temp i8 POS_NAME = i8( FROM ); POS_NAME SYMBOL( i8( TO ) ); POS_NAME += i8( STEP ) )
#define range_step( POS_NAME, FROM, TO, STEP )\
	_range_step( POS_NAME, FROM, TO, STEP, <=, __COUNTER__ )

#define range( POS_NAME, FROM, TO ) range_step( POS_NAME, FROM, TO, 1 )

#define iter_step( POS_NAME, SIZE, STEP )\
	_range_step( POS_NAME, 0, SIZE, STEP, <, __COUNTER__ )
#define iter( POS_NAME, SIZE ) _range_step( POS_NAME, 0, SIZE, 1, <, __COUNTER__ )

#define iter_grid( X_NAME, Y_NAME, WIDTH, HEIGHT )\
	iter( Y_NAME, HEIGHT ) iter( X_NAME, WIDTH )

#define _repeat( N_TIMES, COUNTER ) iter( JOIN( _REP_, COUNTER ), N_TIMES )
#define repeat( N_TIMES ) _repeat( N_TIMES, __COUNTER__ )

///////

#define if_nothing( ARG... ) if( ARG is nothing )
#define if_something( ARG... ) if( ARG isnt nothing )
//
#define any( ARGS... ) ( CHAIN(,, or, ARGS ) )
#define all( ARGS... ) ( CHAIN(,, and, ARGS ) )
#define none( ARGS... ) ( not( any( ARGS ) ) )
#define not_all( ARGS... ) ( not all( ARGS ) )
//
#define if_any( ARGS... ) if( any( ARGS ) )
#define if_all( ARGS... ) if( all( ARGS ) )
#define if_none( ARGS... ) if( none( ARGS ) )
#define if_not_all( ARGS... ) if( not_all( ARGS ) )
//
#define while_any( ARGS... ) while( any( ARGS ) )
#define while_all( ARGS... ) while( all( ARGS ) )
#define while_none( ARGS... ) while( none( ARGS ) )
#define while_not_all( ARGS... ) while( not_all( ARGS ) )
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

#define new_ref( TYPE, AMOUNT... ) to( TYPE ref, calloc( size_of( TYPE ), DEFAULT( 1, AMOUNT ) ) )
#define new_bytes( AMOUNT... ) malloc( DEFAULT( 1, AMOUNT ) )

#define bytes_copy( FROM_REF, FROM_SIZE, TO_REF ) memcpy( TO_REF, FROM_REF, FROM_SIZE )
#define bytes_copy_until( FROM_REF, TO_REF, CHAR, MAX_SIZE ) memccpy( TO_REF, FROM_REF, CHAR, MAX_SIZE )
#define bytes_copy_until_any( FROM_REF, TO_REF, DELIMS ) memcpy( TO_REF, FROM_REF, strcspn( FROM_REF, DELIMS ) )
#define bytes_copy_within( FROM_REF, FROM_SIZE, TO_REF ) memmove( TO_REF, FROM_REF, FROM_SIZE )
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
		temp const n2 _PASTE_SIZE = bytes_measure( FROM_REF );\
		bytes_copy_move( FROM_REF, _PASTE_SIZE, TO_REF );\
	}\
	END_DEF

#define bytes_set_move( BYTE, TO_REF ) val_of( TO_REF++ ) = BYTE

#define bytes_end( BYTES ) val_of( BYTES ) = '\0'

embed anon ref _ref_resize( anon ref r, size_t type_size, size_t old_count, size_t new_count )
{
	temp anon ref new_ptr = realloc( r, type_size * new_count );
	if( new_ptr isnt nothing and new_count > old_count )
	{
		bytes_clear( to( byte ref, new_ptr ) + ( type_size * old_count ), type_size * ( new_count - old_count ) );
	}
	out new_ptr;
}
#define ref_resize( REF, OLD_COUNT, NEW_COUNT ) _ref_resize( REF, size_of( type_of_ref( REF ) ), OLD_COUNT, NEW_COUNT )

#define bytes_resize( REF, NEW_SIZE... ) realloc( REF, DEFAULT( 1, NEW_SIZE ) )

///////

#define PACKED __attribute__( ( packed ) )

#define variant struct

#define _type_make( NAME, REF... )\
	type_from( struct NAME REF ) NAME;\
	struct PACKED NAME
#define type( NAME ) _type_make( NAME )

#define object( NAME ) _type_make( NAME, ref )
#define object_fn( OBJECT, FN, ARGS... )\
	fn OBJECT##_##FN( OBJECT this COMMA_IF_ARGS( ARGS ) ARGS )
#define new_object( OBJECT ) new_ref( type_of_ref( OBJECT ) )

#define make( TYPE, ELEMENT_VALUES... ) ( ( TYPE ) { ELEMENT_VALUES } )

//

#define fusion( NAME )\
	type_from( union NAME ) NAME;\
	union PACKED NAME

#define group( NAME, TYPE... )\
	type_from( DEFAULT( byte, TYPE ) ) NAME;\
	enum NAME

///////

#define declare_bytes( NAME, SIZE, OPTIONAL_BYTES... )\
	byte NAME[ SIZE ] PASTE_IF_ARGS( =, OPTIONAL_BYTES ) DEFAULT(, OPTIONAL_BYTES );\
	byte ref NAME##_ref = NAME + size_of_bytes( DEFAULT( "", OPTIONAL_BYTES ) )

///////

#define print( BYTES ) fputs( BYTES, stdout )
#define print_size( BYTES, SIZE ) fwrite( BYTES, 1, SIZE, stdout )

#define print_newline( ... ) print_size( "\n", 1 )

///////

#define MIN( A, B ) pick( ( A ) < ( B ), A, B )
#define MIN3( A, B, C ) MIN( A, MIN( B, C ) )
#define MIN4( A, B, C, D ) MIN3( A, B, MIN( C, D ) )
#define MIN5( A, B, C, D, E ) MIN4( A, B, C, MIN( D, E ) )

#define MAX( A, B ) pick( ( A ) > ( B ), A, B )
#define MAX3( A, B, C ) MAX( A, MAX( B, C ) )
#define MAX4( A, B, C, D ) MAX3( A, B, MAX( C, D ) )
#define MAX5( A, B, C, D, E ) MAX4( A, B, C, MAX( D, E ) )

#define MEDIAN( A, B, C ) pick( ( A ) > ( B ), pick( ( B ) > ( C ), B, MIN( A, C ) ), pick( ( A ) > ( C ), A, MIN( B, C ) ) )
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
	}

FUNCTION_GROUP_N( 1 );
FUNCTION_GROUP_I( 1 );

FUNCTION_GROUP_N( 2 );
FUNCTION_GROUP_I( 2 );

FUNCTION_GROUP_N( 4 );
FUNCTION_GROUP_I( 4 );
FUNCTION_GROUP_R( 4 );

FUNCTION_GROUP_N( 8 );
FUNCTION_GROUP_I( 8 );
FUNCTION_GROUP_R( 8 );

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

#define terminal_set_format( FORMAT ) print_size( format_##FORMAT, size_of( format_##FORMAT ) )
//
#define terminal_set_rgb( R, G, B ) print( format_rgb( R, G, B ) )
#define terminal_set_color( COLOR ) terminal_set_format( COLOR )
#define terminal_set_dark_color( COLOR ) terminal_set_format( dark_##COLOR )
#define terminal_unset_color() terminal_set_format( color_default )
#define terminal_set_bg_rgb( R, G, B ) print( format_bg_rgb( R, G, B ) )
#define terminal_set_bg_color( COLOR ) terminal_set_format( bg_##COLOR )
#define terminal_set_bg_dark_color( COLOR ) terminal_set_format( bg_dark_##COLOR )
#define terminal_unset_bg_color() terminal_set_format( bg_default )
//
#define terminal_set_bold() terminal_set_format( bold )
#define terminal_set_dim() terminal_set_format( dim )
#define terminal_set_italic() terminal_set_format( italic )
#define terminal_set_underline() terminal_set_format( underline )
#define terminal_set_blink() terminal_set_format( blink )
#define terminal_set_reverse() terminal_set_format( reverse )
#define terminal_set_hidden() terminal_set_format( hidden )
#define terminal_set_strikethrough() terminal_set_format( strikethrough )
//
#define terminal_unset_bold() terminal_set_format( no_bold )
#define terminal_unset_italic() terminal_set_format( no_italic )
#define terminal_unset_underline() terminal_set_format( no_underline )
#define terminal_unset_blink() terminal_set_format( no_blink )
#define terminal_unset_reverse() terminal_set_format( no_reverse )
#define terminal_unset_hidden() terminal_set_format( no_hidden )
#define terminal_unset_strikethrough() terminal_set_format( no_strikethrough )
//
#define terminal_reset_format() terminal_set_format( reset )

//

group( terminal_color, n2 )
{
	terminal_white,
	terminal_red,
	terminal_yellow,
	terminal_green,
	terminal_cyan,
	terminal_blue,
	terminal_magenta,
	terminal_gray,
	terminal_dark_red,
	terminal_dark_yellow,
	terminal_dark_green,
	terminal_dark_cyan,
	terminal_dark_blue,
	terminal_dark_magenta,
};

#define terminal_clear() system( PICK( OS_WINDOWS, "cls", "clear" ) )

embed byte ref get_terminal_input()
{
	perm byte terminal_input[ KB( 1 ) ] = "";
	fgets( terminal_input, size_of_bytes( terminal_input ), stdin );
	out terminal_input;
}

///////

#define is_letter( BYTE ) ( ( ( n4( BYTE ) | 0x20 ) - 'a' ) < 26 )
#define is_number( BYTE ) ( ( n4( BYTE ) - '0' ) < 10 )

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
							bytes_paste_move( SEPARATOR, out_bytes );
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
							if( is_disable )
							{
								bytes_paste_move( format_no_underline, out_bytes );
							}
							else
							{
								bytes_paste_move( format_underline, out_bytes );
							}
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
							if( is_disable )
							{
								bytes_paste_move( format_no_italic, out_bytes );
							}
							else
							{
								bytes_paste_move( format_italic, out_bytes );
							}
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
							if( is_disable )
							{
								bytes_paste_move( format_no_bold, out_bytes );
							}
							else
							{
								bytes_paste_move( format_bold, out_bytes );
							}
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
								if( is_bg is yes )
								{
									bytes_paste_move( format_bg_default, out_bytes );
								}
								else
								{
									bytes_paste_move( format_color_default, out_bytes );
								}
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
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_gray, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_white, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_gray, out_bytes );
											}
											else
											{
												bytes_paste_move( format_white, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'r' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_red, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_red, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_red, out_bytes );
											}
											else
											{
												bytes_paste_move( format_red, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'y' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_yellow, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_yellow, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_yellow, out_bytes );
											}
											else
											{
												bytes_paste_move( format_yellow, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'g' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_green, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_green, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_green, out_bytes );
											}
											else
											{
												bytes_paste_move( format_green, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'c' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_cyan, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_cyan, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_cyan, out_bytes );
											}
											else
											{
												bytes_paste_move( format_cyan, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'b' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_blue, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_blue, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_blue, out_bytes );
											}
											else
											{
												bytes_paste_move( format_blue, out_bytes );
											}
										}
										skip;
									}
									//
									when( 'm' )
									{
										if( is_bg is yes )
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_bg_dark_magenta, out_bytes );
											}
											else
											{
												bytes_paste_move( format_bg_magenta, out_bytes );
											}
										}
										else
										{
											if( is_dark is yes )
											{
												bytes_paste_move( format_dark_magenta, out_bytes );
											}
											else
											{
												bytes_paste_move( format_magenta, out_bytes );
											}
										}
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
	declare_bytes( format, KB( 2 ) );
	print_size( format, _format_bytes( format_ref, format_bytes, args ) );
}

///////

#define PATH_MAX_SIZE 260

///////

group( entry_type )
{
	entry_unknown,
	entry_files,
	entry_folders,
	entry_any = ( entry_files | entry_folders )
};

embed n2 get_entries( const byte const_ref dir, byte entries[][ PATH_MAX_SIZE ], const n2 max_entries, const entry_type type )
{
	temp n2 count = 0;
	temp n2 len = bytes_measure( dir );
	byte path[ PATH_MAX_SIZE ];
	anon ref handle;
	bytes_copy( dir, len, path );

	#if OS_LINUX
		struct dirent ref entry;
		struct stat stat_buf;
		handle = opendir( dir );
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
					bytes_copy( entry->d_name, entry_size, entries[ count++ ] );
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
			temp flag is_dir = flag( entry.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY );
			if( type is entry_any or ( type is entry_folders and is_dir is yes ) or ( type is entry_files and is_dir is no ) )
			{
				bytes_copy( entry.cFileName, bytes_measure( entry.cFileName ), entries[ count++ ] );
			}
		}
		while( count < max_entries and FindNextFile( handle, ref_of( entry ) ) );
		FindClose( handle );
	#endif
	return count;
}

#define get_files( DIR, OUT_ENTRIES, MAX_ENTRIES ) get_entries_in_folder( DIR, OUT_ENTRIES, MAX_ENTRIES, entry_files )
#define get_folders( DIR, OUT_ENTRIES, MAX_ENTRIES ) get_entries_in_folder( DIR, OUT_ENTRIES, MAX_ENTRIES, entry_folders )

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
		out( attrib isnt INVALID_FILE_ATTRIBUTES and ( attrib &FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

embed flag file_exists( const byte const_ref path )
{
	#if OS_LINUX
		struct stat st;
		out( stat( path, ref_of( st ) ) is 0 and S_ISREG( st.st_mode ) );
	#elif OS_WINDOWS
		DWORD attrib = GetFileAttributesA( path );
		out( attrib isnt INVALID_FILE_ATTRIBUTES and not ( attrib &FILE_ATTRIBUTE_DIRECTORY ) );
	#endif
}

///////

#define path( FOLDERS... ) CHAIN(,, SEPARATOR, FOLDERS )

fn path_up_folder( byte const_ref path )
{
	temp byte ref p = path + bytes_measure( path );
	while( p > path and val_of( --p ) isnt val_of( SEPARATOR ) );
	if( p > path ) val_of( p ) = '\0';
}

///////

type_from( FILE ref ) os_file_handle;

type( file )
{
	byte path[ PATH_MAX_SIZE ];
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
	perm byte exe_path[ PATH_MAX_SIZE ] = "";
	#if OS_LINUX
		readlink( "/proc/self/exe", exe_path, PATH_MAX_SIZE );
	#elif OS_WINDOWS
		GetModuleFileNameA( nothing, exe_path, PATH_MAX_SIZE );
	#endif
	out exe_path;
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

//

#define DECLARE_TYPE_MULTI( TYPE )\
	DECLARE_TYPE_2D( TYPE );\
	DECLARE_TYPE_3D( TYPE );\
	DECLARE_TYPE_4D( TYPE );\
	DECLARE_TYPE_2D_FN( TYPE );\
	DECLARE_TYPE_3D_FN( TYPE );\
	DECLARE_TYPE_4D_FN( TYPE )

//

DECLARE_TYPE_MULTI( n1 );
DECLARE_TYPE_MULTI( i1 );
DECLARE_TYPE_MULTI( n2 );
DECLARE_TYPE_MULTI( i2 );
DECLARE_TYPE_MULTI( n4 );
DECLARE_TYPE_MULTI( i4 );
DECLARE_TYPE_MULTI( r4 );
DECLARE_TYPE_MULTI( n8 );
DECLARE_TYPE_MULTI( i8 );
DECLARE_TYPE_MULTI( r8 );

#define AREA( x2 ) ( x2.w * x2.h )

///////

#define _main_fn out_state main( const i4 input_count, const byte const_ref const_ref input_bytes )
#define start _main_fn

/////// /////// /////// /////// /////// /////// ////////
