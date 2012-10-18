/*
 * Log.hpp
 */

#ifndef _LOG_HPP
#define _LOG_HPP

#define TRED 1
#define TGREEN 2
#define TYELLOW 3
#define TNORMAL 4
#define TWHITE 5
#define TBLUE 6
#define TPURPLE 7

namespace fbi
{
	class CLog
	{
	public:
		CLog()
		{
			UNIXTIME = time(&UNIXTIME);
		}

		void Init(uint8 loglevel)
		{
			log_level = loglevel;
		}

		void Color(unsigned int color)
		{
			const char* colorstrings[TBLUE+1] = {
				"",
				"\033[22;31m",
				"\033[22;32m",
				"\033[01;33m",
				//"\033[22;37m",
				"\033[0m",
				"\033[01;37m",
				"\033[1;34m",
			};

			//fputs(colorstrings[color], stdout);
			cout << colorstrings[color];
		}

		void Notice(const char * source, const char * format, ...)
		{
			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			cout << "N ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TNORMAL);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		void Info(const char * source, const char * format, ...)
		{
			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			cout << "I ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TPURPLE);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		void Success(const char * source, const char * format, ...)
		{
			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			Color(TGREEN);
			cout << "S ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TGREEN);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		void Error(const char * source, const char * format, ...)
		{
			if(log_level < 1)
				return;

			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			Color(TRED);
			cout << "E ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TRED);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		void Warning(const char * source, const char * format, ...)
		{
			if(log_level < 2)
				return;

			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			Color(TYELLOW);
			cout << "E ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TYELLOW);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		void Debug(const char * source, const char * format, ...)
		{
			if(log_level < 3)
				return;

			boost::mutex::scoped_lock scoped_lock(mutex);
			Color(TNORMAL);
			Time();
			Color(TBLUE);
			cout << "E ";

			if(*source)
			{
				Color(TWHITE);
				cout << source << ":" << " ";
				Color(TBLUE);
			}

			cout << format << endl;
			Color(TNORMAL);
		}

		/*#define LARGERRORMESSAGE_ERROR 1
		#define LARGERRORMESSAGE_WARNING 2
	
		void LargeErrorMessage(uint32 Colour, ...)
		{
			boost::mutex::scoped_lock scoped_lock(mutex);

			vector<char*> lines;
			char* pointer;
			va_list ap;
			va_start(ap, Colour);
		
			size_t i, j, k;
			pointer = va_arg(ap, char*);
			while(pointer != NULL)
			{
				lines.push_back(pointer);
				pointer = va_arg(ap, char*);
			}

			delete pointer;

			if(Colour == LARGERRORMESSAGE_ERROR)
				Color(TRED);
			else
				Color(TYELLOW);

			printf("*********************************************************************\n");
			printf("*                        MAJOR ERROR/WARNING                        *\n");
			printf("*                        ===================                        *\n");

			for(vector<char*>::iterator itr = lines.begin(); itr != lines.end(); ++itr)
			{
				i = strlen(*itr);
				j = (i <= 65) ? 65 - i : 0;

				printf("* %s", *itr);
				for(k = 0; k < j; ++k)
					printf(" ");

				printf(" *\n");
			}

			printf("*********************************************************************\n");
			printf("Sleeping for 5 seconds.\n");
			Sleep(5000);
			Color(TNORMAL);
		}*/

	protected:
		boost::mutex mutex;
		uint8 log_level;

		// Frissiti az idõt a jelenlegire
		time_t UNIXTIME;

		inline void Time()
		{
			tm* t = localtime(&UNIXTIME);
			printf("%02u:%02u ", t->tm_hour, t->tm_min);
		}
	};
}

#endif
