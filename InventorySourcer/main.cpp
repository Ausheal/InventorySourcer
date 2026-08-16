#include <cstdio>
#include <curl/curl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

namespace py = pybind11;

struct Listing
{
    std::string itemID;
    std::string title;
    std::string url;
    double price; 
    double quantity; 
    bool inStock; 
};

size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userp)
{
    size_t totalSize = size * nmemb;

    std::string* response =
        static_cast<std::string*>(userp);

    response->append(
        static_cast<char*>(contents),
        totalSize
    );

    return totalSize;
}


Listing ebay_finder(const std::string& product_search)
{
    Listing result;

    std::string token = "YOUR_ACCESS_TOKEN";

    CURL* curl = curl_easy_init();

    if (!curl)
    {
        std::cerr << "Failed to initialize CURL\n";
        return 1;
    }

    std::string response;

    std::string url =
        "https://api.ebay.com/buy/browse/v1/item_summary/search"
        "?q="+ product_search+
        "&limit=50";

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        url.c_str()
    );

    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        ("Authorization: Bearer " + token).c_str()
    );

    headers = curl_slist_append(
        headers, "Content-Type: application/json"
    );

    headers = curl_slist_append(
        headers,
        "X-EBAY-C-MARKETPLACE-ID: EBAY_US"
    );

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        WriteCallback
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response
    );

    CURLcode result =
        curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        std::cerr
            << "CURL error: "
            << curl_easy_strerror(result)
            << "\n";
    }
    else
    {
        std::cout << response << "\n";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);



    result.title = ;
    result.itemID = "123456789";
    result.url = ;
    result.price = 249.99;
    result.quantity = 1;
    result.inStock = false; 
    return result;
}
Listing manual_add(const std::string& new_title, const std::string& new_ID, const std::string&& new_url double new_price,
    int new_quantity, bool new_stock)
{
    Listing result;

    result.title = new_title;
    result.itemID = new_ID;
    result.url = new_url;
    result.price = new_price;
    result.quantity = new_quantity;
    result.inStock = new_stock;
    return result;
}


PYBIND11_MODULE(_inventory_sourcer, m)
{
    m.doc() = "Inventory Source Finder for tech flipping";
    py::class_<Listing>(m, "Listing")
        .def(py::init<>())
        .def_readwrite("itemID", &Listing::itemID)
        .def_readwrite("title", &Listing::title)
        .def_readwrite("url", &Listing::url)
        .def_readwrite("price", &Listing::price)
        .def_readwrite("quantity", &Listing::quantity)
        .def_readwrite("inStock", &Listing::inStock);

    m.def("ebay_finder", &ebay_finder,
        "finds ebay listings and stores data in database ");
    m.def("manual_add", &manual_add,
        "allows you to manually add listing and stores data in database ");
}

