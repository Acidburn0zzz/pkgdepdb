#ifndef PKGDEPDB_PROGRAM_H__
#define PKGDEPDB_PROGRAM_H__

namespace pkgdepdb {

namespace JSONBits {
  static const unsigned int
    Query = (1<<0),
    DB    = (1<<1);
}

enum LogLevel {
  Debug, Message, Print, Warn, Error
};

struct Config {
  string database_         = "";
  uint   verbosity_        = 0;
  bool   quiet_            = false;
  bool   package_depends_  = true;
  bool   package_filelist_ = true;
  uint   json_             = 0;
  uint   max_jobs_         = 0;
  uint   log_level_        = LogLevel::Message;

  Config();
  Config(Config&&) = delete;
  Config(const Config&) = delete;
  ~Config();

  bool ReadConfig();
  void Log(uint level, const char *msg, ...) const;

  static const char *ParseJSONBit(const char *bit, uint &opt_json);
  static bool str2bool(const string&);

 private:
  bool ReadConfig(std::istream&, const char *path);
};

} // ::pkgdepdb

#endif
