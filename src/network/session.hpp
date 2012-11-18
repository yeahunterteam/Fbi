/*
 * session.hpp
 */

namespace fbi
{
	namespace network
	{
		using namespace boost::system;
		using namespace fbi::irc;
		using boost::asio::ip::tcp;

		class session : public ChatParticipant, public boost::enable_shared_from_this<session>
		{
		public:
			session(boost::asio::io_service& io_service);
			~session();

			void start();
			void deliver(const string& msg);
			void deliver(const ChatMessage& msg);

			static const int PingInterval = 300; // 5 miniutes

			tcp::socket& GetSocket()
			{
				return socket_;
			}

		private:
			void HandleIgnore(const string& command_id, const string& data, string& answer);
			void HandleUnknown(const string& command_id, const string& data, string& answer);
			void HandleConnect(const string& command_id, const string& data, string& answer);
			void HandleQuit(const string& command_id, const string& data, string& answer);
			void HandlePing(const string& command_id, const string& data, string& answer);
			void HandlePong(const string& command_id, const string& data, string& answer);
			void HandleName(const string& command_id, const string& data, string& answer);
			void HandleMessage(const string& command_id, const string& data, string& answer);
			void HandleChannelList(const string& command_id, const string& data, string& answer);
			void HandleAddChannel(const string& command_id, const string& data, string& answer);
			void HandleRemoveChannel(const string& command_id, const string& data, string& answer);

			void InitHandlers();
			void handle_command(const string& command_data);
			void handle_read(const error_code& error);
			void handle_write(const error_code& error);
			void HandleRegisterTimeout(const error_code& error);
			void HandleConnectionTimeout(const error_code& error);

			void WriteNextMessage();
			void cleanup();

			// egyéb egyszerűsítési módszerek az üzenetek küldéséhez.
			void success(string msg);
			void unknown(string msg);
			void ping(string msg);
			void pong(string msg);
			void newname(string msg);

			uint64 UnixTime();
			void StopIrc();

		private:
			typedef void (session::*MessageHandler)(const string& command_id, const string& data, string& answer);

			tcp::socket socket_;
			boost::asio::streambuf buffer_;
			ChatMessageQueue write_msgs_;
			bool initialized_;
			bool authorized_;
			boost::asio::deadline_timer register_timeout_;
			boost::asio::deadline_timer connection_timeout_;
			bool closing_connection_;
			bool ping_sent_;
			string cliensname;
			boost::mutex sync_;
			map<string, MessageHandler> registration_handlers_;
			map<string, MessageHandler> message_handlers_;
			vector<string> enabledlist_;

			boost::unordered_map<string, ircinfo> IrcClientMap;
			boost::unordered_map<string, io_service> IoServiceMap;
		};
	}
}
