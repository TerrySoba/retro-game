#include "animation.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <sstream>
#include <map>
#include <codecvt>

std::string escapeRegex(const std::string& str)
{
    const boost::regex esc("([.^$|()\\[\\]{}*+?\\\\])");
    const std::string rep("(?1\\\\$&)");
    std::string result =
            boost::regex_replace(str, esc, rep,
                                 boost::regex_constants::match_default |
                                 boost::format_all);
    return result;
}

std::string globToRegex(const std::string& str)
{
    const boost::regex esc("\\\\\\*");
    const std::string rep("([0-9]+)");
    std::string result = boost::regex_replace(str, esc, rep);
    return result;
}


int toInt(const std::string& str)
{
    std::stringstream ss;
    ss << str;
    int number;
    ss >> number;
    return number;
}





std::wstring toWString(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string toString(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

std::string toString(const std::string& str)
{
	return str;
}

std::string toString(const boost::filesystem::path& path)
{
	return toString(path.native());
}


std::map<int, std::string> getAnimationFilenames(const std::string& globName)
{
    // split globName into path and filename
    boost::filesystem::path p(globName);
    auto filename = p.filename();
    auto path = p.remove_filename();

    auto regexString = globToRegex(escapeRegex(toString(filename)));

    boost::regex reg(regexString);

    std::map<int, std::string> results;

    // now iterate over all files in directory
    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
    {
        for (auto it = boost::filesystem::directory_iterator(path);
             it != boost::filesystem::directory_iterator();
             ++it)
        {
            boost::smatch result;
            std::string f = toString(it->path().filename());

            // check if file matches regular expression
            if (boost::regex_match(toString(it->path().filename()), result, reg))
            {
                std::string match = result[0];
                std::string number = result[1];
                auto matchedFile = toString(path) + "/" + f;
                results[toInt(number)] = matchedFile;
            }
        }
    }
    return results;
}


Animation::Animation(const std::string& basename)
{
    auto files = getAnimationFilenames(basename);

    for (auto& file : files)
    {
        m_images.emplace_back(file.second);
    }

    if (m_images.empty())
    {
        throw Exception("Too few images in animation.");
    }
}

void Animation::setFrame(uint32_t frame)
{
    m_currentFrame = frame;
}

uint32_t* Animation::getData()
{
    return m_images[m_currentFrame % m_images.size()].getData();
}

uint32_t Animation::getWidth()
{
    return m_images[m_currentFrame % m_images.size()].getWidth();
}

uint32_t Animation::getHeight()
{
    return m_images[m_currentFrame % m_images.size()].getHeight();
}

uint32_t Animation::getFrameCount()
{
    return m_images.size();
}
