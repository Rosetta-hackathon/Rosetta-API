#include <thread>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <restbed>
#include <jsoncpp/json/json.h>

using namespace std;
using namespace restbed;

void get_method_handler( const shared_ptr< Session > session )
{
	Json::Reader reader;
    	Json::Value obj;
	
	reader.parse("/home/cag0/rosetta/return.json",obj);
    session->close( OK, obj.asString(), { { "Content-Length", "17" }, { "Connection", "close" } } );
}

void service_ready_handler( Service& )
{
    fprintf( stderr, "Hey! The service is up and running." );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );

    auto service = make_shared< Service >( );
    service->publish( resource );
    service->set_ready_handler( service_ready_handler );
    service->start( settings );

    return EXIT_SUCCESS;
}
