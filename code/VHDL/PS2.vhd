library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.smd152_pkg.all;

entity PS2 is
  port ( Clk     : in std_logic;
         Reset   : in  std_logic;
         LS      : out std_logic_vector(0 to 6);
         RS      : out std_logic_vector(0 to 6);
         PS2Clk  : in  std_logic;
         PS2Data : in  std_logic;         
         ShiftRegOut: out std_logic_vector(0 to 8);
         FifoWrEnable: out std_logic);
end PS2;

architecture Keyboard of PS2 is
  ----------------------------
  -- Component declarations --
  ----------------------------
  component OneShot
    port (
      Clk, Reset : in  std_logic;
      D          : in  std_logic;
      Pulse      : out std_logic);
  end component;
  
  component ShiftReg
    port (
      Clk      : in  std_logic;
      Enable   : in  std_logic;
      D        : in  std_logic;
      Q        : out std_logic_vector(8 downto 0));
  end component;

  component ParityChecker
    port (
      D  : in  std_logic_vector(8 downto 0);
      OK : out std_logic);
  end component;

  component ReceiverFSM
    port (
      PS2ClkPulse : in  std_logic;
      PS2Data     : in  std_logic;
      ParityOK    : in  std_logic;
      Clk, Reset  : in  std_logic;
      Shift_en    : out std_logic;
      FifoWrite   : out std_logic);
  end component;

  component fifo
    port (
      clk   : in  std_logic;
      sinit : in  std_logic;
      din   : in  std_logic_vector(7 downto 0);
      wr_en : in  std_logic;
      rd_en : in  std_logic;
      dout  : out std_logic_vector(7 downto 0);
      full  : out std_logic;
      empty : out std_logic);
  end component;

  component Timer
    port (
      Clk, Reset : in  std_logic;
      FifoEmpty  : in  std_logic;
      FifoRead   : out std_logic);
  end component;

  -- Tells Synplicity that the FIFO is a "black box" 
  attribute syn_black_box         : boolean;
  attribute syn_black_box of fifo : component is true;

  -- signal declarations go here
  signal InternalPS2Clk : std_logic;
  signal OneShotPulse : std_logic;
  signal ParityOkPulse : std_logic;
  signal InternalPS2Data : std_logic;
  signal ShiftEnalbePulse : std_logic;
  signal EnableFifoPulseRead : std_logic;
  signal EnableFifoPulseWrite : std_logic;
  signal InternalPS2Bus9 : std_logic_vector(8 downto 0);
  signal InternalFifoBus8 : std_logic_vector(7 downto 0);
  signal InternalFifoEmptyPulse : std_logic;
  signal ResetInternal : std_logic;
  signal InternalFDC : std_logic;       -- THIS IS JUST SFTER THE FLIP AFTER TIMER
  
  
  
begin -- Keyboard

  OneShot_1: OneShot
    port map (
      Clk   => Clk,
      Reset => ResetInternal,
      D     =>InternalPS2Clk ,
      Pulse =>OneShotPulse );
  
  ReceiverFSM_1 : ReceiverFSM
    port map (
      ParityOK    =>ParityOkPulse ,
      PS2ClkPulse =>OneShotPulse ,
      PS2Data     =>InternalPS2Data ,
      Clk         =>Clk ,
      Reset       => ResetInternal ,
      Shift_en    => ShiftEnalbePulse ,
      FifoWrite   =>EnableFifoPulseWrite );

  ShiftReg_1 : ShiftReg
    port map (
      Clk      =>Clk ,
      Enable   =>ShiftEnalbePulse ,
      D        =>InternalPS2Data ,
      Q        =>InternalPS2Bus9 );  

  ParityChecker_1: ParityChecker
    port map (
      D  =>InternalPS2Bus9 ,
      OK => ParityOkPulse );
  
  fifo_1 : fifo
    port map (
      clk   => Clk,
      sinit =>  ResetInternal,
      din   => InternalPS2Bus9(7 downto 0) ,
      wr_en =>  EnableFifoPulseWrite,
      rd_en => EnableFifoPulseRead ,
      dout  =>  InternalFifoBus8,
      full  => open ,
      empty => InternalFifoEmptyPulse);


  Timer_1: Timer
    port map (
      Clk       =>Clk ,
      Reset     => ResetInternal,
      FifoEmpty =>InternalFifoEmptyPulse ,
      FifoRead  => EnableFifoPulseRead );


  process(ResetInternal,Clk)
  begin
    -- use this process to implement all flip-flops, except the Reset
    -- flip-flop, shown in figure 5. The ROMs will also be implemented
    -- here. The ROMs are simply function calls to functions described
    -- in smd152_pkg (you have to write that function!)
   ----------------------------------------------------------------------------
    -- FIRST i WILL MODEL THE RESET AND DATA TRANSFER FOR THE 2 FDP FLIPFLOPS and
    -- the FDCE ; (Asynchronous Reset)AND RisingEdge!
  
   if ResetInternal = '1' then
       InternalFDC <= '0';
       RS <= "0000000";
       LS <= "0000000";
       InternalPS2Clk <= '0';
       InternalPS2Data <= '0';
    elsif rising_edge(Clk) then
       InternalFDC <=EnableFifoPulseRead; 
      InternalPS2Data <= PS2Data;
      InternalPS2Clk  <= PS2Clk;
      if InternalFDC = '1' then
        RS <= bin2Led(unsigned(InternalFifoBus8(3 downto 0)));
        LS <= bin2Led(unsigned(InternalFifoBus8(7 downto 4)));
         end if;
      end if;

  end process;
   ResetInternal <= Reset;
   ShiftRegOut  <= InternalPS2Bus9;
   FifoWrEnable <=  EnableFifoPulseWrite;   
end Keyboard;







