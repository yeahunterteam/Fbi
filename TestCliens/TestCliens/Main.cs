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
				writer = new StreamWriter(stream); 

				writer.WriteLine("CONNECT");
				writer.Flush();

				string inputLine = string.Empty;

				while(true)
				{
					while((inputLine = reader.ReadLine()) != null)
					{
						Console.WriteLine(inputLine);
						writer.WriteLine("PASS csá");
						writer.Flush();
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
	}
}