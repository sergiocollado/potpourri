library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Arbiter is
  port (
    ---------------------------------------------------------------------------
    -- From core.
    ---------------------------------------------------------------------------
    Addr_FromCore : in  std_logic_vector(31 downto 0);
    DataOut       : in  std_logic_vector(31 downto 0);
    DataIn        : out std_logic_vector(31 downto 0);
    Wen           : in  std_logic;      -- active high
    Ren           : in  std_logic;      -- active high
    ---------------------------------------------------------------------------
    -- To/from keyboard
    ---------------------------------------------------------------------------
    Ren_KB        : out std_logic;
    Addr_KB       : out std_logic_vector(31 downto 0);
    Data_FromKB   : in  std_logic_vector(31 downto 0);
    ---------------------------------------------------------------------------
    -- To/from UART
    ---------------------------------------------------------------------------
    Ren_UART      : out std_logic;
    Wen_UART      : out std_logic;
    Addr_UART     : out std_logic_vector(31 downto 0);
    Data_FromUART : in  std_logic_vector(31 downto 0);
    Data_ToUART   : out std_logic_vector(31 downto 0);
    ---------------------------------------------------------------------------
    -- To/from data memory.
    ---------------------------------------------------------------------------
    Addr_DM       : out std_logic_vector(31 downto 0);
    Data_ToDM     : out std_logic_vector(31 downto 0);
    Wen_DM        : out std_logic;
    Data_FromDM   : in  std_logic_vector(31 downto 0)
    );
end Arbiter;

architecture RTL of Arbiter is
signal test : std_logic_vector(31 downto 0);
begin  -- RTL

  process(Wen, Ren, Addr_FromCore,Data_FromDm, Data_FromUART, Data_FromKB, DataOut)
  begin  -- process
--default
    DataIn      <= Data_FromDM;
   
    Addr_DM <= Addr_FromCore;
    Data_ToDM   <=DataOut;
    Wen_DM      <= '0';
    Ren_KB      <= '0';
    Addr_KB     <= Addr_FromCore;
    Ren_UART    <= '0';
    Wen_UART    <= '0';
    Addr_UART   <= Addr_FromCore;
    Data_ToUART <= DataOut;
    Wen_DM      <= Wen;

    if Addr_FromCore = x"FFFF_0000" or Addr_FromCore = x"FFFF_0001" or Addr_FromCore = x"FFFF_0003" or  Addr_FromCore = x"FFFF_0004" then
      DataIn <= Data_FromKB;
      Ren_KB <= Ren;
    elsif Addr_FromCore = x"FFFF_0008" or Addr_FromCore = x"FFFF_0009" or Addr_FromCore = x"FFFF_0010" or Addr_FromCore = x"FFFF_000A" or Addr_FromCore = x"FFFF_000B" or  Addr_FromCore = x"FFFF_000C" then
      DataIn <= Data_FromUART;          --from uart to core
      Data_ToUART <= DataOut;           -- from core to uart 
      Ren_UART <= Ren;
      Wen_UART <= Wen;
      else
       Wen_DM <= Wen;
    end if;
    
  end process;
 
  

end RTL;
