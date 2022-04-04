#!/usr/bin/rdmd

import std.stdio;
import std.string;
import std.math;
import std.algorithm;
import std.conv;

void usage( string prog_name )
{
	auto prog = prog_name.split("/");
	writeln( "Usage: ", prog[$-1], " FILE" );
}

double median( double[] array )
{
	array.sort();
	if( array.length % 2 == 0 )
		return array[ $ / 2 ];
	else
		return ( array[ ($ - 1) / 2 ] + array[ $ / 2 ] ) / 2;
}

double pop_standard_deviation( double[] array )
{
	auto mean = array.mean;
	array[] -= mean;
	array[] ^^= 2;
	return sqrt( sum( array ) / array.length );
}

int main( string[] args )
{
	if( args.length != 2 )
	{
		usage( args[0] );
		return 1;
	}

	auto file = File( args[1] );
	auto range = file.byLine();
	int success;
	double time;
	double[] times;
	
	foreach( line; range )
	{
		auto words = line.split(": ");
		if( words != null && !words[0].empty )
		{
			if( startsWith( words[0], "Satisfaction error" ) )
			{
				if( to!double( words[1] ) == 0 )
					++success;
			}
			else
				if( startsWith( words[0], "Search time" ) )
				{
					auto get_rid_of_ms = words[1].split("ms")[0];
					auto runtime = to!double( get_rid_of_ms.split( "= " )[1] );
					time += runtime;
					times ~= runtime;
				}
		}
	}

	if( success != 100 )
		writefln( "Warning: we do not have 100 solutions but only ", success, ".\n" );

	double mean = times.mean.quantize(0.01);
	writeln( "Mean time: ", mean, "ms" );
	writeln( "Median time: ", median(times).quantize(0.01), "ms" );
	writeln( "Min time: ", times.minElement.quantize(0.01), "ms" );
	writeln( "Max time: ", times.maxElement.quantize(0.01), "ms" );
	writeln( "Std dev: ", pop_standard_deviation(times).quantize(0.01), "ms" );

	return 0;
}
