#include "log.h"
#include <map>

namespace gq {
const char * LogLevel::ToString (LogLevel::Level level)
{
    switch (level)
    {
#define XX(name) \
        case LogLevel::name : \
             return #name; \
             break;
        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
#undef XX
        default :
           return "UNKNOW"
    }
    return "UNKONW";
}

class MessageFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getContent();
      }
} //MessageFormatItem 

class LevelFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << LogLevel::ToString(level);
      }
} //LevelFormatItem 

class ElapseFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getElapse();
      }
} //ElapseFormatItem

class NameFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << logger -> getName();
      }
} //NameFormatItem

class ThreadIdFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getThreadId();
      }
} //ThreadIdFormatItem

class FiberIdFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getFiberId();
      }
} //FiberIdFormatItem

class DateTimeFormatItem : public LogFormatter::FormatItem {
   public :
      DateTimeFormatItem (const std::string & format = "%Y:%m:%d %H:%M:%S") : m_format (format)
      {

      }
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getTime();
      }
   private :
      std::string m_format;  
} //DateTimeFormatItem

class FilenameFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getFile();
      }
} //FilenameFormatItem

class LineFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << event -> getLine();
      }
} //LineFormatItem

class NewLineFormatItem : public LogFormatter::FormatItem {
   public :
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << std::endl;
      }
} //LineFormatItem

class StringFormatItem : public LogFormatter::FormatItem {
   public :
      StringFormatItem(const std::string & str) : FormatItem(str), m_string(str) {}
      std::string format (std::ostream & os, LogLevel::Level level, LogEvent::ptr event) override
      {
          os << m_string;
      }
   private :
      std::string m_string;
} //StringFormatItem

/********      Logger 实现  **********/
Logger::Logger (const std::string & name = "root") : m_name (name)
{
    
}
   
void Logger::addAppender (LogAppender::ptr appender)
{
    m_appenders.push_back (appender);
}

void Logger::delAppender (LogAppender::ptr appender)
{
    //注意，最好不好在用循环删除迭代器中的数据，会让后续的迭代器失效。
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
    {
        if (*it == appender)
        {
            m_appenders.erase (it);
            break;
        }
    }

}

void Logger::log(LogLevel::Level level, LogEvent::ptr event)
{
    if (level >= m_level)
    {
		auto self = shared_from_this();
        for (auto & i : m_ppenders)
        {
            i -> log (self, level, event);
        }
    }

}

void Logger::debug (LogEvent::ptr event)
{
    log(LogLevel::DEBUG, event);

}

void Logger::info (LogEvent::ptr event)
{
    log(LogLevel::INFO, event);
}

void Logger::warn (LogEvent::ptr event)
{
    log(LogLevel::WARN, event);

}

void Logger::fatal (LogEvent::ptr event)
{
    log(LogLevel::FATAL, event);

}

void Logger::error (LogEvent::ptr event)
{
    log(LogLevel::DEBUG, event);

}

/********* StdoutAppender 实现    ************/
void StdoutLogAppender::log (std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override
{
    if (level >= m_level)
    {
	std::cout << m_formatter -> format (logger, level, event);
	      
    }

}

/********* FileAppender 实现    ************/
FileLogAppender::FileLogAppender (const std::string & filename) : m_filename (filename)
{

}
void FileLogAppender::log (std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override
{
    if (level >= m_level)
    {
        m_filestream << m_formatter -> format(logger, level, event);
    }

}
bool FileLogAppender::reopen ()
{
    if (m_filestream)
    {
        m_filestream.close ();
    }
    m_filestream.open (m_filename);

    return !!m_filestream;
}
/******* LogFormatter 实现   ****************/
LogFormatter::LogFormatter (const std::string & pattern) : m_pattern (pattern)
{

}
std::string LogFormatter::format (std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    std::stringstream ss;
    for (auto & i : m_items)
    {
        i -> format (ss, logger, level, event);
    }
    return ss.str();
}
void LogFormatter::init ()
{
    std::vector<std::tuple<<std::string, std::string, int>> vec;
    std::string nstr;
    size_t last_pos = 0;
    for (size_t i = 0; i < m_pattern.size(); ++i)
    {
        if (m_pattern[i] != '%')
        {
             nstr.append(1, m_pattern[i]);
             continue;
        }

        if ((i + 1) < m_pattern.size())
        {
             if (m_pattern[i + 1] == '%')
             {
                  nstr.append(1, '%');
                  continue;
             }
        }
        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while (n < m_pattern.size()) 
        {
             if (isspace(m_pattern[n]))
             {
                 break;
             }
             if (fmt_status == 0) 
             {
                 if (m_pattern[n] == '{')
		 {
		     str = m_pattern.substr (i + 1, n - i);    
                     fmt_status = 1;   //解析格式
                     ++n;
                     fmt_begin = n;
                     continue;
		 }
             }
             if (fmt_status == 1) 
             {
                 if (m_pattern[n] == '}')
		 {
		     fmt = m_pattern.substr (fmt_begin + 1, n - fmt_begin);    
                     fmt_status = 2;   //结束解析格式
                     break;
		 }
             }
        }
        if (fmt_status == 0)
        {
            if (!nstr.empty())
            {
                vec.push_back (std::make_tuple(nstr, "", 0));
            }
            
            str = m_pattern.substr (i + 1, n - i - 1);
            vec.push_back (std::make_tuple(str, fmt, 1));
        }
        else if (fmt_status == 1) 
        {
            std::cout << "pattern parse error :" << m_pattern << " - " << m_pattern[i] << std::endl;
            vec.push_back (std::make_tuple("<error>", fmt, 0));
        }
        else if (fmt_status == 2) 
        {
            vec.push_back (std::make_tuple(str, fmt, 1));
            i = n;
        }
        
    }
    if (!nstr.empty())
    {
        vec.push_back (std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<FormatItem::ptr(const std::string & str)> > s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string & fmt) {return FormatItem::ptr(new C (fmt));}}

        XX(m, MessageFormatItem),
        XX(p, LevelFormatItem),
        XX(r, ElapseFormatItem),
        XX(c, NameFormatItem),
        XX(t, ThreadIdFormatItem),
        XX(n, NewLineFormatItem),
        XX(d, DateTimeFormatItem),
        XX(f, FilenameFormatItem),
        XX(l, LineFormatItem),
#undef XX

    };
    for (auro & i : vec)
    {
        if (std::get<2>(i) == 0)
        {
             m_items.push_back (FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        }
        else 
        {
             auto it = s_format_itmes.find (std::get<0>(i));
             if (it == s_format_items.end())
             {
                 m_items.push_back (FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>"))); 
             }
             else
             {
                 m_itmes.push_back (it->second(std::get<1>(i)));
             }
        }
        std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " << std::get<2>(i) << std::endl;
    }
    //%m -- 消息体
    //%p -- level
    //%r -- 启动后的时间
    //%c -- 日志名称
    //%t -- 线程id
    //%n -- 回车换行
    //%d -- 时间
    //%f -- 文件名
    //%l -- 行号
}


}
