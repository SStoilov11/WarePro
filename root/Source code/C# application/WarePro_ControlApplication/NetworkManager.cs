using System.Net;
using System.Net.Sockets;

namespace WarePro_ControlApplication
{
    internal class NetworkManager
    {
        const string ADDRESS = "0.0.0.0";
        const int PORT = 8888;

        StreamWriter writer;
        StreamReader reader;

        public NetworkManager() { }

        public async Task<string> StartServer()
        {
            IPAddress ip = IPAddress.Parse(ADDRESS); // Parse the IP address
            IPEndPoint endPoint = new IPEndPoint(ip, PORT); // Create an endpoint

            // Create a TCP/IP socket
            Socket listner = new Socket(ip.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint and listen for incoming connections
            listner.Bind(endPoint);

            // Start listening
            listner.Listen(1);

            // Wait for a connection
            Socket clientSocket = await listner.AcceptAsync();

            // Create a stream to read and write data
            NetworkStream stream = new NetworkStream(clientSocket);
            writer = new StreamWriter(stream);
            reader = new StreamReader(stream);

            string ipport = GetServerIP(endPoint);
            return ipport; // Return true if the server started successfully
        }

        public string GetServerIP(IPEndPoint endPoint)
        {
            string ip = endPoint.Address.ToString();
            string port = endPoint.Port.ToString();
            return $"Server started at {ip}:{port}";
        }

        public async Task<string> ReadData()
        {
            // Read data from stream until ";"
            string? data = await reader.ReadLineAsync();

            string[] strings = data.Split(';'); // Split the incoming data to separate 
            string command = strings[0]; // $MOVEA1; -> $MOVEA1 -> MOVEA1 -> MOVE + A1
            string commandType = command.Substring(1, 4); // MOVE
            string commandValue = command.Substring(5); // A1

            return command + " " + commandType + " " + commandValue;
        }

        public async Task WriteData(string data)
        {
            await writer.WriteLineAsync(data);
            await writer.FlushAsync();
        }

    }
}
