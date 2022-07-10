#pragma once

#include <string>
#include <vector>
#include "../../AliveLibCommon/Sys_common.hpp"

constexpr inline char kDirSeperator = '\\';

// TODO: Lots of stuff missing, needs to do utf8 -> utf16 on windows
class FileSystem final
{
public:
    class Path final
    {
    public:
        Path& Append(const std::string& directory)
        {
            if (!directory.empty() && directory[directory.size() - 1] == kDirSeperator)
            {
                ALIVE_FATAL("Directory ends with slash");
            }
            if (!mPath.empty())
            {
                mPath += kDirSeperator;
            }
            mPath += directory;
            return *this;
        }

        Path Parent() const
        {
            const auto pos = mPath.find_last_of(kDirSeperator);
            if (pos != std::string::npos)
            {
                Path parent;
                parent.mPath = mPath.substr(0, pos);
                return parent;
            }
            return {};
        }

        const std::string& GetPath() const
        {
            return mPath;
        }

    private:
        std::string mPath;
    };

    void Save(const Path& path, const std::vector<u8>& data)
    {
        CreateDirectory(path.Parent());
        FILE* pFile = ::fopen(path.GetPath().c_str(), "wb");
        if (pFile)
        {
            ::fwrite(data.data(), 1, data.size(), pFile);
            ::fclose(pFile);
        }
    }

    void CreateDirectory(const Path& path)
    {
        std::string dirPart;

        std::string fullPath = path.GetPath();

        auto dirPos = fullPath.find_first_of(kDirSeperator);
        do
        {
            if (dirPos != std::string::npos)
            {
                dirPart = dirPart + fullPath.substr(0, dirPos);
                ::CreateDirectoryA(dirPart.c_str(), nullptr);
                dirPart.append(1, kDirSeperator);
                fullPath = fullPath.substr(dirPos + 1);
                dirPos = fullPath.find_first_of(kDirSeperator);
            }
        }
        while (dirPos != std::string::npos);

        ::CreateDirectoryA(path.GetPath().c_str(), nullptr);
    }

};
