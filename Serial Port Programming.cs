using System;                                   // Allows usage of classes from the System Name Space
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.IO.Ports;

namespace Serial_Test                           // container for classes and other namespaces
{
    class Program                               // container for data and methods, functionality
    {
        static void Main(string[] args)
        {
            SerialPort mySerialPort = new SerialPort("COM1", 9600);  // define the serial port and baudrate
            try
            {

                mySerialPort.Open(); // opens the serial port

                mySerialPort.Write("Hello World");              // writes text to the serial port
                mySerialPort.Write("This is a test");           

                byte[] byteArray = { 1, 2, 3, 4, 5, 6, 7, 8 };  // writes an array to the serial port
                mySerialPort.Write(byteArray, 0, 8 );


                char[] charArray = { 'a', 'b', 'c', 'd', 'e', 'f' }; // writes an array of characters to the serial port
                mySerialPort.Write(charArray, 0, 6);




                
                byte b = (byte)mySerialPort.ReadByte();     // reads a byte
                char c = (char)mySerialPort.ReadChar();     // reads a char
                string line = mySerialPort.ReadLine();      // reads a whole line
                string all = mySerialPort.ReadExisting();   // reads everything in the buffer

                // printing results
                Console.WriteLine("Byte: " + b);
                Console.WriteLine("Char: " + c);
                Console.WriteLine("Line: " + line);
                Console.WriteLine("All: " + all);


                mySerialPort.Close();  // close the port
            }
            catch (IOException ex)
            {
                Console.WriteLine("ERROR"); // throws error message for any exceptions
            }
        }
    }
}