#include "P4A.h"

using namespace std;

P4A::P4A()
{
    ///P4A header
    output_header.push_back(0x50);
    output_header.push_back(0x34);
    output_header.push_back(0x41);

    ///P4A version
    output_header.push_back(0x01);
}

int P4A::GetFileSize(string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    int fsize = in.tellg();
    return fsize;
}

void P4A::LoadFile(string filename)
{
    original_path.push_back(filename);
    cout << "Original path is: " << filename << endl;

    string plain_filename = filename.substr(filename.find_last_of("\\")+1);

    filenames.push_back(plain_filename);
    cout << "File name is: " << plain_filename << endl;

    int filesize = GetFileSize(filename);
    filesizes.push_back(filesize);
    cout << "File size is: " << filesize << endl;
}

void P4A::CreateDictionary()
{
    for(int i=0; i<filenames.size(); i++)
    {
        dictionary_size += 9 + filenames[i].size();
    }

    cout << "Dictionary size: " << dictionary_size << endl;

    file_offset = dictionary_size;

    for(int i=0; i<filenames.size(); i++)
    {
        string file = filenames[i];
        int filename_length = file.size();
        int8_t length_8bit = filename_length;

        output_dictionary.push_back(length_8bit);

        for(int a=0; a<file.size(); a++)
        {
            output_dictionary.push_back(file[a]);
        }

        ///file offset
        output_dictionary.push_back(char(uint32_t(file_offset)));
        output_dictionary.push_back(char(uint32_t(file_offset) >> 8));
        output_dictionary.push_back(char(uint32_t(file_offset) >> 16));
        output_dictionary.push_back(char(uint32_t(file_offset) >> 24));

        ///file size
        file_size = filesizes[i];
        cout << "File size: " << file_size << endl;

        output_dictionary.push_back(char(uint32_t(file_size)));
        output_dictionary.push_back(char(uint32_t(file_size) >> 8));
        output_dictionary.push_back(char(uint32_t(file_size) >> 16));
        output_dictionary.push_back(char(uint32_t(file_size) >> 24));

        file_offset += file_size;
    }

    /// 1101 = 13
    /// >> 1
    /// 0110 = 6
    /// >> 1
    /// 0011 = 3
    /// >> 1
    /// 0001 = 1
    /// >> 1
    /// 0000 = 0

    /// 1101|
    /// 0110|1
    /// 0011|01
    /// 0001|101
    /// 0000|1101

    output_header.push_back(char(uint32_t(dictionary_size-8)));
    output_header.push_back(char(uint32_t(dictionary_size-8) >> 8));
    output_header.push_back(char(uint32_t(dictionary_size-8) >> 16));
    output_header.push_back(char(uint32_t(dictionary_size-8) >> 24));
}

void P4A::Debug_SaveDictionary(string filename)
{
    ofstream file(filename,std::ios_base::binary);

    while(file.is_open())
    {
        cout << "Writing header..." << endl;
        for(int i=0; i<output_header.size(); i++)
        {
            file.put(output_header[i]);
        }

        cout << "Writing dictionary..." << endl;
        for(int i=0; i<output_dictionary.size(); i++)
        {
            file.put(output_dictionary[i]);
        }

        cout << "Writing files..." << endl;
        for(int i=0; i<filenames.size(); i++)
        {
            ifstream get_file(filenames[i], std::ios_base::binary);

            char ch;

            while(get_file.get(ch))
            file.put(ch);

            get_file.close();
        }

        file.close();

        cout << "Done!" << endl;
    }
}

void P4A::ReadDictionary(std::string filename)
{
    ifstream file(filename, std::ifstream::binary);

    char header[3];
    file.read(header,3);

    cout << header[0] << header[1] << header[2] << endl;
    if(header[0] == 'P' and header[1] == '4' and header[2] == 'A')
    {
        cout << "Correct archive format!" << endl;
        ///reading

        ///8 bits = 1 byte, 0-255 (0-FF)
        ///signed 8 bit integer: -127 - 128
        ///unsigned 8 bit integer: 0 - 255
        /// file version - 01
        /// unsigned - 1
        /// signed - -126

        ///16 bits = 2 bytes, 0 - 65535

        uint8_t file_version;

        file.seekg(3);
        file.read(reinterpret_cast<char*>(&file_version), 1);

        if(file_version == 1)
        {
            cout << "Detected Archive version 1" << endl;

            uint32_t file_dictionary_size;

            file.seekg(4);
            file.read(reinterpret_cast<char*>(&file_dictionary_size), 4);

            cout << "Dictionary size is: " << file_dictionary_size << endl;

            int file_data_pointer = file_dictionary_size + 8;

            p4a_offset = 8;
            vector<string> file_names;
            vector<int> file_offsets;
            vector<int> file_sizes;

            while(p4a_offset < file_data_pointer)
            {
                uint8_t filename_length;

                file.seekg(p4a_offset);
                file.read(reinterpret_cast<char*>(&filename_length), 1);
                p4a_offset += 1;

                file.seekg(p4a_offset);
                char file_name[filename_length];
                file.read(file_name,filename_length);

                string str_filename(file_name);
                str_filename = str_filename.substr(0,filename_length);

                cout << "Filename: " << str_filename << endl;

                p4a_offset += filename_length;

                uint32_t file_offset;

                file.seekg(p4a_offset);
                file.read(reinterpret_cast<char*>(&file_offset), 4);
                cout << "File offset: " << file_offset << endl;

                p4a_offset += 4;

                uint32_t file_size;

                file.seekg(p4a_offset);
                file.read(reinterpret_cast<char*>(&file_size), 4);
                cout << "File size: " << file_size << endl;

                p4a_offset += 4;
            }
        }
        else
        {
            cout << "Incorrect file version!" << endl;
        }
    }
    else
    {
        cout << "Incorrect file type" << endl;
        ///exit
    }

    file.close();
}
