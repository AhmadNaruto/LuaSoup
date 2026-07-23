#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/buffer.hpp"
#include "nrp/modules/url.hpp"
#include "nrp/modules/crypto.hpp"
#include "nrp/modules/regex.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Running Native Modules & JSoup / LexSoup Scraper Tests..." << std::endl;

    // 1. Test JSoup Scraper APIs (Document::parse, select, select_first, select_last, attr, text, html)
    std::string sample_html = 
        "<html><head><title>LuaSoup Scraper Title</title></head>"
        "<body><div id=\"main\" class=\"container card\"><h1 class=\"title\">Header 1</h1>"
        "<ul class=\"list\"><li class=\"item\">Item A</li><li class=\"item active\">Item B</li><li class=\"item\">Item C</li></ul>"
        "</div></body></html>";

    auto doc = nrp::modules::html::Document::parse(sample_html);
    assert(doc != nullptr);
    assert(doc->title() == "LuaSoup Scraper Title");

    // JSoup .select() and .select_first()
    auto items = doc->select(".item");
    assert(items.size() == 3);

    auto first_item = doc->select_first(".item");
    assert(first_item != nullptr);
    assert(first_item->text() == "Item A");

    auto last_item = doc->select_last(".item");
    assert(last_item != nullptr);
    assert(last_item->text() == "Item C");

    // JSoup class manipulation (.hasClass, .addClass, .removeClass)
    auto main_card = doc->select_first("#main");
    assert(main_card != nullptr);
    assert(main_card->has_class("card"));
    assert(main_card->attr("id") == "main");

    main_card->add_class("shadow");
    assert(main_card->has_class("shadow"));

    main_card->remove_class("card");
    assert(!main_card->has_class("card"));

    // JSoup DOM Element Traversal (first_element_child, next_element_sibling)
    auto list = doc->select_first(".list");
    assert(list != nullptr);
    auto child1 = list->first_element_child();
    assert(child1 != nullptr && child1->text() == "Item A");
    auto child2 = child1->next_element_sibling();
    assert(child2 != nullptr && child2->text() == "Item B");

    // 2. Test JSON Parser & Serializer
    std::string sample_json = "{\"name\":\"LuaSoup\",\"version\":1.0,\"active\":true}";
    auto json_val = nrp::modules::json::Json::parse(sample_json);
    assert(json_val.is_object());

    // 3. Test Buffer Encoding
    nrp::modules::buffer::Buffer buf("Hello LuaSoup!");
    std::string hex = buf.to_hex();
    std::string b64 = buf.to_base64();
    assert(!hex.empty() && !b64.empty());

    // 4. Test URL Parser
    auto url = nrp::modules::url::URL::parse("https://luasoup.dev:8080/api/v1/search?q=nrp#heading");
    assert(url.scheme == "https" && url.host == "luasoup.dev");

    // 5. Test Crypto SHA-256
    std::string hash = nrp::modules::crypto::Crypto::sha256("LuaSoup");
    assert(hash.length() == 64);

    // 6. Test Regex
    nrp::modules::regex::Regex re("\\d+");
    assert(re.test("Item 123"));

    std::cout << "All Native Modules & JSoup / LexSoup Scraper Tests Passed Successfully!" << std::endl;
    return 0;
}
