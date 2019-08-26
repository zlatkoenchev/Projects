using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace HFHome
{
    class HexFileHandler
    {
        byte[] buff;
        long BuffSize,addrlo,addrhi;
        int align;

        public long GetLoAddress()
        {
            return addrlo;
        }

        public long GetHiAddress()
        {
            return addrhi;
        }

        public long GetAlign()
        {
            return align;
        }

        public char GetASCIINibble(byte b)
        {
            if (b > 9)
                return (char)(b + 0x41);
            else
                return (char)(b + 0x30);
        }

        public string GetASCIIByte(byte b)
        {
            string s = ""; 
                s+= GetASCIINibble((byte)(b >> 4));
            s += GetASCIINibble((byte)(b & 0x0F));
            return s;
        }

        public string GetASCIIWordMSB(int b)
        {
            string s = "";
            b = b & 0xFFFF;
            s += GetASCIIByte((byte)(b >> 8));
            s += GetASCIINibble((byte)(b & 0xFF));
            return s;
        }

        public int GetHexWord(string s)
        {
            return (((int)GetHexByte(s)) * 256 + GetHexByte(s.Substring(2)));
        }

        public byte GetHexByte(string s)
        {
            return (byte)(GetHexChar(s[0]) * 16 + GetHexChar(s[1]));
        }

        public byte GetHexChar(char c)
        {
            if (((int)c) > 0x40)
            {
                return (byte)((int)c - 0x37);
            }
            return (byte)((int)c-0x30);
        }

        public HexFileHandler(string filename,long maxsize, byte fillvalue,int alignment)
        {

            StreamReader reader = new StreamReader(filename);
            
            BuffSize = maxsize;
            align = alignment;
            
            buff = new byte[maxsize];

            for (int j = 0; j < maxsize; j++)
            {
                buff[j] = fillvalue;
            }
            addrlo = 0xFFFF;
            addrhi = 0;

            string ins = reader.ReadLine(); 
            while (ins.Length > 8)
            {
                if (ins[0] == ':')
                {
                    switch (ins[8])
                    {
                        case '0'://data record
                        {
                            long addr = GetHexWord(ins.Substring(3,4));
                            long len =  GetHexByte(ins.Substring(1,2));
                            if (addrlo > addr)
                            {
                                addrlo = addr;
                            }
                            for (int i = 0; i < len; i++)
                            {
                                if (addr<maxsize)
                                {
                                    buff[addr] = GetHexByte(ins.Substring(9+i+i, 2));
                                    addr++;
                                }
                            }
                            if (addrhi < addr)
                            {
                                addrhi = addr;
                            }
                            
                        }
                        break;
                    }
                    ins = reader.ReadLine();//read next line
                    if (ins == null)
                    {
                        ins = "";
                    }
                }
            }
            reader.Close();
        }

        public byte GetHexDataByte(long startaddr)
        {
            return (buff[startaddr]);
        }

        public byte[] GetHexDataAligned(long startaddr)
        {

            if (align > 0)
            {
                byte[] bb = new byte[align];
                for (int i = 0; i < align; i++)
                {
                    bb[i] = buff[startaddr + i];
                }
                return bb;
            }
            else return null;
        }

        public string GetASIIDataAligned(long startaddr)
        {
            string s = "";
            for (int i = 0; i < align; i++)
            {
                s = s + GetASCIIByte(buff[startaddr + i]);
            }
            return s;
        }
    }
}
