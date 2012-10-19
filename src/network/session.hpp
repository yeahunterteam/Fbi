/*
 * session.hpp
 */

namespace fbi
{
	namespace network
	{
		using namespace boost::system;
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
			void Authorize();
			void MessageIgnore(const string& command_id, const string& data, string& answer);
			void MessageUnknown(const string& command_id, const string& data, string& answer);
			void MessageConnect(const string& command_id, const string& data, string& answer);

			/*void MessageQuit(const string& command_id, const string& data, string& answer)
			{
				//cerr<<"!!!: quit\n";
				cleanup();
			}

			void MessagePing(const string& command_id, const string& data, string& answer)
			{
				stringstream strstr;
				WriteServerHeaderNoNick(strstr, "PONG")<<bridge_.GetServerName()<<" :"<<data<<"\n";
				answer = strstr.str();
				if(!ping_sent_)
				{
					connection_timeout_.expires_from_now(boost::posix_time::seconds(PingInterval));
					connection_timeout_.async_wait(boost::bind(&session::HandleConnectionTimeout, shared_from_this(),
								boost::asio::placeholders::error));
				}
			}

			void MessagePong(const string& command_id, const string& data, string& answer)
			{
				stringstream strstr;
				if(ping_sent_)
				{
					ping_sent_ = false;
					connection_timeout_.expires_from_now(boost::posix_time::seconds(PingInterval));
					connection_timeout_.async_wait(boost::bind(&session::HandleConnectionTimeout, shared_from_this(),
								boost::asio::placeholders::error));
				}
				answer = strstr.str();
			}*/

			void handle_command(const string& command_data);
			void handle_read(const error_code& error);
			void handle_write(const error_code& error);
			void HandleRegisterTimeout(const error_code& error);
			void HandleConnectionTimeout(const error_code& error);

			void WriteNextMessage();
			void cleanup();

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
			boost::mutex sync_;
			map<string, MessageHandler> registration_handlers_;
			map<string, MessageHandler> message_handlers_;
		};
	}
}
