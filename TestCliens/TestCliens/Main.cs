using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace TestCliens
{
	class MainClass
	{
		public static StreamWriter writer;

		public static void Main (string[] args)
		{
			Console.WriteLine("Start!");
			NetworkStream stream;
			TcpClient irc;
			StreamReader reader;

			try
			{
				irc = new TcpClient("127.0.0.1", 6009);
				stream = irc.GetStream();
				reader = new StreamReader(stream);
				writer = new StreamWriter(stream) { AutoFlush = true }; 

				writer.WriteLine("CONNECT");
				writer.WriteLine("NAME Teszt");
				string channels = string.Empty;

				for(int i = 0; i < 47; i++)
					channels += ", #schumix" + i;

				writer.WriteLine("CHANNELLIST :{0}", channels.Remove(0, 2));

				//writer.WriteLine("CHANNELLIST :#schumix, #schumix2, #schumixdd, #schumixd, #schumix4444, #schumix44566, #schumix12333, #schumix344656, #schumix56457, #schumixjfgfs, #schumix321kkdl, #schumix12kckd");

				string inputLine = string.Empty;

				while(true)
				{
					new Thread(() => Ping()).Start();
					new Thread(() => ConsoleCommands()).Start();

					while((inputLine = reader.ReadLine()) != null)
					{
						Console.WriteLine(inputLine);

						if(inputLine.Contains("PING"))
							writer.WriteLine("PONG :asd");

						//writer.WriteLine("PASS csá");
						Thread.Sleep(1000);
					}

					writer.Close();
					reader.Close();
					irc.Close();
				}
			}
			catch(Exception e)
			{
				Console.WriteLine(e.ToString());
				Thread.Sleep(5000);
				string[] argv = { };
				Main(argv);
			}
		}

		private static void Ping()
		{
			while(true)
			{
				writer.WriteLine("PING :asd");
				Thread.Sleep(30*1000);
			}
		}

		private static void ConsoleCommands()
		{
			while(true)
			{
				string message = System.Console.ReadLine();
				if(message == null || IncomingInfo(message))
					continue;

				Console.WriteLine("Console: ismeretlen: {0}", message);
				Thread.Sleep(1000);
			}
		}

		public static bool IncomingInfo(string info)
		{
			try
			{
				string[] Info = info.Split(' ');
				string cmd = Info[0].ToLower();

				if(cmd == "test")
				{
					if(Info.Length < 2)
					{
						Console.WriteLine("CERROR: nincs elég paraméter megadva!");
						return false;
					}

					if(Info[1].ToLower() == "message")
					{
						writer.WriteLine("MESSAGE: Csá irc.");
						writer.WriteLine("MESSAGE: Irc.");
						Console.WriteLine("Console: Teszt üzenet elküldve.");
						return true;
					}
				}

				return false;
			}
			catch(Exception e)
			{
				Console.WriteLine("CERROR: {0}", e.Message);
				return true;
			}
		}
	}
}
