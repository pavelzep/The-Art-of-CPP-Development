// #include "solution.h"
#include "test_runner.h"
#include "json.h"
#include "xml.h"

using namespace std;

Json::Document XmlToJson(const Xml::Document& doc) {

    vector<Json::Node> result;

    for (const Xml::Node& n : doc.GetRoot().Children()) {
        result.emplace_back(map<string, Json::Node>{
            {"category", Json::Node{ n.AttributeValue<string>("category") }},
            {"amount", Json::Node(stoi(n.AttributeValue<string>("amount"))) }
        });
    }

    return Json::Document(Json::Node(std::move(result)));
}

Xml::Document JsonToXml(const Json::Document& doc, string root_name) {

    Xml::Node root(move(root_name), {});
    for (const auto& n : doc.GetRoot().AsArray()) {
        root.AddChild(Xml::Node("spend", {
          {"category", n.AsMap().at("category").AsString()},
          {"amount", to_string(n.AsMap().at("amount").AsInt())},
            }));
    }
    return Xml::Document(root);
}

void TestJsonToXml() {
    using Json::Node;

    const Json::Document json_doc{ Json::Node(vector<Json::Node>{
      Node(map<string, Node>{
        {"category", Node("food")}, {"amount", Node(2500)}
      }),
      Node(map<string, Node>{
        {"category", Node("transport")}, {"amount", Node(1150)}
      }),
      Node(map<string, Node>{
        {"category", Node("restaurants")}, {"amount", Node(5780)}
      }),
      Node(map<string, Node>{
        {"category", Node("clothes")}, {"amount", Node(7500)}
      }),
      Node(map<string, Node>{
        {"category", Node("travel")}, {"amount", Node(23740)}
      }),
      Node(map<string, Node>{
        {"category", Node("sport")}, {"amount", Node(12000)}
      }),
    }) };

    const string root_name = "month";
    const auto xml_doc = JsonToXml(json_doc, root_name);
    const Xml::Node& root = xml_doc.GetRoot();

    ASSERT_EQUAL(root.Name(), root_name);
    const vector<Xml::Node>& children = root.Children();
    ASSERT_EQUAL(children.size(), 6u);

    const vector<string> expected_category = {
      "food", "transport", "restaurants", "clothes", "travel", "sport"
    };
    const vector<int> expected_amount = { 2500, 1150, 5780, 7500, 23740, 12000 };

    for (size_t i = 0; i < children.size(); ++i) {
        using Json::Node;

        const string feedback_msg = "i = " + std::to_string(i);
        const Xml::Node& c = children[i];
        AssertEqual(c.Name(), "spend", feedback_msg);
        AssertEqual(c.AttributeValue<string>("category"), expected_category[i], feedback_msg);
        AssertEqual(c.AttributeValue<int>("amount"), expected_amount[i], feedback_msg);
    }
}

void TestXmlToJson() {

    Xml::Node root("july", {});
    root.AddChild({ "spend", {{"category", "travel"}, {"amount", "23400"}} });
    root.AddChild({ "spend", {{"category", "food"}, {"amount", "5000"}} });
    root.AddChild({ "spend", {{"category", "transport"}, {"amount", "1150"}} });
    root.AddChild({ "spend", {{"category", "sport"}, {"amount", "12000"}} });
    const Xml::Document xml_doc(std::move(root));

    const auto json_doc = XmlToJson(xml_doc);

    const auto& items = json_doc.GetRoot().AsArray();
    ASSERT_EQUAL(items.size(), 4u);

    const vector<string> expected_category = { "travel", "food", "transport", "sport" };
    const vector<int> expected_amount = { 23400, 5000, 1150, 12000 };
    

    for (size_t i = 0; i < items.size(); ++i) {
        const map<string, Json::Node>& item = items[i].AsMap();
        const string feedback_msg = "i = " + std::to_string(i);
        AssertEqual(item.at("category").AsString(), expected_category[i], feedback_msg);
        AssertEqual(item.at("amount").AsInt(), expected_amount[i], feedback_msg);
    }
}