/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __PINYIN__
#define __PINYIN__

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

typedef std::unordered_map<std::string, std::string> PinYinArray;
typedef std::unordered_map<std::string, std::string>::iterator PinYinIter;

class PinYinInit 
{
public:
    explicit PinYinInit() 
    {
        std::string word, pinyin;
        double rate;
        unsigned int flag;

        m_file.open(LIBCPPJIEBAR_DIR + std::string("/rawdict_utf8_65105_freq.txt"));
        while (m_file >> word >> rate >> flag >> pinyin) {
            if (word.size() > m_wordSize)
                continue;

            m_pinyinInits[word] = pinyin[0];
            m_pinyins[word] = pinyin;
        }
        m_file.close();
    }

    ~PinYinInit() {}

    PinYinArray pinyinInits() const { return m_pinyinInits; }

    std::string getInitials(std::string str) 
    {
        std::string ret;
        
        for (unsigned int i = 0; i < str.size() / m_wordSize; i++) {
            std::string word = str.substr(i * m_wordSize, m_wordSize);
#if DEBUG
            printf("%x %x %x\n", word[0], word[1], word[2]);
#endif
            ret += m_pinyinInits[word];
        }

        return ret.size() ? ret : str;
    }

    std::string get(std::string str) 
    {
        std::string ret;

        for (unsigned int i = 0; i < str.size() / m_wordSize; i++) {
            std::string word = str.substr(i * m_wordSize, m_wordSize);
            ret += m_pinyins[word];
        }

        return ret.size() ? ret : str;
    }

private:
    PinYinArray m_pinyinInits;
    PinYinArray m_pinyins;
    std::ifstream m_file;
    const unsigned int m_wordSize = 3;
};

#endif // __PINYIN__

#if 0
int main(int argc, char* argv[]) 
{
    PinYinInit* objPinYinInit = new PinYinInit;

    std::cout << "澀兔子 " << objPinYinInit->getInitials("澀兔子") << std::endl;
    std::cout << "の " << objPinYinInit->getInitials("の") << std::endl;
    std::cout << "Leslie " << objPinYinInit->getInitials("Leslie") << std::endl;

    delete objPinYinInit;
    objPinYinInit = nullptr;
    
    return 0;
}
#endif
