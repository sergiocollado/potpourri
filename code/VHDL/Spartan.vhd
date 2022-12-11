library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.MUPS_pkg.all;

entity Spartan is
  port (
      Clk      : in  std_logic;
      SW1      : in  std_logic;
      -- Keyboard I/O
      PS2Clk   : in  std_logic;
      PS2Data  : in  std_logic;
      -- UART I/O
      RS232_TD : out std_logic;

      --CE for devices on peripheral bus(act. low)
      Flash_CE : out std_logic;
      RAM_CE   : out std_logic;
      SDRAM_CE : out std_logic;
      ETH_CE   : out std_logic;
      USB_CE   : out std_logic;
      NV_CS0   : out std_logic;
      NV_CS1   : out std_logic
      );
end Spartan;

architecture RTL of Spartan is

component Arbiter
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
end component Arbiter;


component PS2 
  port ( SW1     : in  std_logic;
         LS      : out std_logic_vector(0 to 6);
         RS      : out std_logic_vector(0 to 6);
         PS2Clk  : in  std_logic;
         PS2Data : in  std_logic;
         Clk      : in  std_logic;
         SHIFTROUT : out std_logic_vector(0 to 8);
         WrEnableF : out std_logic;
         renable   : in std_logic;      --arbiter
         ControlIn  :in std_logic_vector(31 downto 0);  --arbiter
         DataOut     :out std_logic_vector(31 downto 0));  --arbiter );

end component PS2;

component UART 
port(
    reset         : in std_logic;
    CLK           : in std_logic;
    Ren_UART      : in std_logic;
    Wen_UART      : in std_logic;
    doutS         : out std_logic;
    Addr_UART     : in std_logic_vector(31 downto 0);
    Data_FromUART : out  std_logic_vector(31 downto 0);
    Data_ToUART   : in std_logic_vector(31 downto 0)
    );  

end component UART;


component memory 
	port (
	addr: IN std_logic_VECTOR(9 downto 0);
	clk: IN std_logic;
	din: IN std_logic_VECTOR(31 downto 0);
	dout: OUT std_logic_VECTOR(31 downto 0);
	we: IN std_logic);
END component memory;

  -- Tells Synplicity that the memory is a "black box" 
  attribute syn_black_box           : boolean;
  attribute syn_black_box of memory : component is true;


component Core 
  port (
    Clk : in std_logic;
    Addressout    : out  std_logic_vector(31 downto 0);
    DataOut       : out  std_logic_vector(31 downto 0);
    DataIn        : in  std_logic_vector(31 downto 0);
    Wen           : out  std_logic; -- active high
    Ren           : out  std_logic; -- active high
    Reset         : in  std_logic);
  
end component Core;

--------signal declaration
signal reset : std_logic;
signal sigarb_1 : std_logic;
signal sigarb_2 : std_logic;
signal sigarb_3 : std_logic_vector(31 downto 0);
signal sigarb_4 : std_logic_vector(31 downto 0);
signal sigarb_5 : std_logic_vector(31 downto 0);
signal sigarb_6 : std_logic_vector(31 downto 0);
signal sigarb_7 : std_logic_vector(31 downto 0);
signal sigarb_8 : std_logic_vector(31 downto 0);
signal sigarb_9 : std_logic;
signal sigarb_10 : std_logic;
signal sigarb_11 : std_logic;
signal sigarb_12 : std_logic_vector(31 downto 0);
signal sigarb_13 : std_logic_vector(31 downto 0);
signal sigarb_14 : std_logic_vector(31 downto 0);
signal sigarb_15 : std_logic_vector(31 downto 0);
signal sigarb_16 : std_logic;
signal sigarb_17 : std_logic_vector(31 downto 0);
signal prueba : std_logic_vector(31 downto 0);
begin  -- RTL
  -- disable components on bus
  Flash_CE <= '1';
  RAM_CE   <= '1';
  SDRAM_CE <= '1';
  ETH_CE   <= '1';
  USB_CE   <= '1';
  NV_CS0   <= '1';
  NV_CS1   <= '1';



  Arbiter_1:Arbiter
  port map(
    ---------------------------------------------------------------------------
    -- From core.
    ---------------------------------------------------------------------------
    Addr_FromCore =>sigarb_6,
    DataOut       =>sigarb_7,
    DataIn        =>sigarb_8,
    Wen           =>sigarb_9,
    Ren           =>sigarb_10,
    ---------------------------------------------------------------------------
    -- To/from keyboard
    ---------------------------------------------------------------------------
    Ren_KB        =>sigarb_11,
    Addr_KB       =>sigarb_12,
    Data_FromKB   =>sigarb_13,
    ---------------------------------------------------------------------------
    -- To/from UART
    ---------------------------------------------------------------------------
    Ren_UART      => sigarb_1,
    Wen_UART      => sigarb_2,
    Addr_UART     => sigarb_3,
    Data_FromUART => sigarb_5,
    Data_ToUART   => sigarb_4,
    ---------------------------------------------------------------------------
    -- To/from data memory.
    ---------------------------------------------------------------------------
    Addr_DM       => sigarb_14,
    Data_ToDM     => sigarb_15,
    Wen_DM        => sigarb_16,
    Data_FromDM   => sigarb_17
    );

PS2_1: PS2 
  port map( SW1    => reset, 
         LS        => open,
         RS        => open,
         PS2Clk    => PS2Clk,
         PS2Data   => PS2Data,  
         Clk       => Clk,
         SHIFTROUT => open,
         WrEnableF => open,
         renable   => sigarb_11,
         ControlIn => sigarb_12,
         DataOut   => sigarb_13
);

UART_1:UART 
port map (
    reset         => reset,
    CLK           =>Clk,
    Ren_UART      =>sigarb_1,
    Wen_UART      =>sigarb_2,
    doutS         =>RS232_TD,
    Addr_UART     =>sigarb_3,
    Data_FromUART =>sigarb_5,
    Data_ToUART   =>sigarb_4
    );  


memory_1:memory 
        port map (
	addr       => sigarb_14(11 downto 2),
	clk        => Clk,
	din        => sigarb_15,
	dout       => sigarb_17,
	we         => sigarb_16
        );


Core_1:Core 
  port map (
    Clk           =>Clk,
    Addressout    =>sigarb_6,
    DataOut       =>sigarb_7,
    DataIn        =>sigarb_8,
    Wen           =>sigarb_9,
    Ren           =>sigarb_10,
    Reset         =>reset);
  

 reset <= not(SW1);
end RTL;










