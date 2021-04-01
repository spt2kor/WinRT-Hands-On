/*
#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

int main()
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());
}

*/
// main.cpp
#include <iostream>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>

using namespace std;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;

void PrintFeed(SyndicationFeed const& syndicationFeed)
{
    cout << "\n ############ PrintFeed start: " << std::this_thread::get_id() << endl << endl;
    for (SyndicationItem const& syndicationItem : syndicationFeed.Items())
    {
        std::wcout << syndicationItem.Title().Text().c_str() << std::endl;
    }

    cout << "\n ############ PrintFeed end: " << std::this_thread::get_id() << endl << endl;

}

IAsyncAction ProcessFeedAsync()
{
    cout << "\n ############ ProcessFeedAsync start: " << std::this_thread::get_id() << endl << endl;

    Uri rssFeedUri{ L"https://blogs.windows.com/feed" };
    SyndicationClient syndicationClient;
    cout << "\n ############ ProcessFeedAsync before feed: " << std::this_thread::get_id() << endl << endl;

    SyndicationFeed syndicationFeed{ co_await syndicationClient.RetrieveFeedAsync(rssFeedUri) };
    cout << "\n ############ ProcessFeedAsync afterfeed: " << std::this_thread::get_id() << endl << endl;

    PrintFeed(syndicationFeed);
    cout << "\n ############ ProcessFeedAsync afterprint: " << std::this_thread::get_id() << endl << endl;

}

int main()
{
    // Here system_clock is wall clock time from 
// the system-wide realtime clock 
    auto timenow =
        chrono::system_clock::to_time_t(chrono::system_clock::now());

    cout << endl << ctime(&timenow) << endl;


    cout << "\n ############ Program started: " << std::this_thread::get_id() << endl << endl;
    winrt::init_apartment();


    cout << "\n ############ inti apart done : " << std::this_thread::get_id() << endl << endl;

    auto processOp{ ProcessFeedAsync() };
    // do other work while the feed is being printed.

    cout << "\n ############ aftr processOp: " << std::this_thread::get_id() << endl << endl;

    //processOp.get(); // no more work to do; call get() so that we see the printout before the application exits.

    cout << "\n ############ exit app: " << std::this_thread::get_id() << endl << endl;


}