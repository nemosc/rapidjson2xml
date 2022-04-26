
int rapidjson_to_pxml(rapidjson::Value& json_value,PXmlNode& xml_node)
{
    //json_value必须是Object
    if(!json_value.IsObject())
    {
        return -1;
    }
    for (auto itr = json_value.MemberBegin();itr != json_value.MemberEnd(); ++itr)
    {
        std::string child_name =  itr->name.GetString();
        rapidjson::Value& child_value = itr->value;
        if(child_value.IsObject())
        {
            std::string xml_data = "<"+child_name+"></"+child_name+">";
            PXmlDocument child_xml_document;
            child_xml_document.Parse(xml_data,"gbk");
            PXmlNode child_xml_node = child_xml_document.GetRoot();
            rapidjson_to_pxml(child_value,child_xml_node);
            xml_node.AddChild(child_xml_node);
        }
        else if(child_value.IsArray())
        {
            std::string xml_data = "<"+child_name+"></"+child_name+">";
            PXmlDocument child_xml_document;
            child_xml_document.Parse(xml_data,"gbk");
            PXmlNode child_xml_node = child_xml_document.GetRoot();
            for(int i = 0;i<child_value.Size();i++)
            {
                rapidjson_to_pxml(child_value[i],child_xml_node);
            }
            xml_node.AddChild(child_xml_node);
        }
        else if(child_value.IsString())
        {
            xml_node.NewCDataChild(child_name,child_value.GetString());
        }
        else if(child_value.IsBool())
        {
            xml_node.NewCDataChild(child_name,child_value.GetBool()?"true":"false");
        }
        else if(child_value.IsInt())
        {
            xml_node.NewCDataChild(child_name,std::to_string(child_value.GetInt()));
        }
        else if(child_value.IsDouble())
        {
            xml_node.NewCDataChild(child_name,std::to_string(child_value.GetDouble()));
        }
        else if(child_value.IsNull())
        {
            xml_node.NewCDataChild(child_name,"");
        }
    }
    return 0;
}
