library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.MUPS_pkg.all;


entity Controller is
  
port (
  CLK           : in std_logic;
  reset         : in std_logic;
  IR_32         : in std_logic_vector(31 downto 0);
  ALUcode       : out std_logic_vector(3 downto 0);
  ---src_a         : out std_logic;
  --src_b         : out std_logic_vector(1 downto 0);
  IRWrite       : out std_logic;
  RegWrite      : out std_logic;
  RegDst        : out std_logic_vector(1 downto 0);
  mem2reg       : out std_logic_vector(1 downto 0);
  loD           : out std_logic;        --source addr
  ALUSrcA       : out std_logic_vector(1 downto 0);
  ALUSrcB       : out std_logic_vector(1 downto 0);
  PCSource      : out std_logic_vector(1 downto 0);
  PCWrite       : out std_logic;   --
  PCWriteCond   : out std_logic;
  signExtend    : out std_logic;        --to AluScrB_IC componete
  MemRead      : out std_logic;
  MemWrite     : out std_logic
  );


end Controller;

architecture RTL  of Controller is
 
  type state is (onecycle,IF1,IF2,IDecode,Addrcomp,Branch,Execute,Execute2,MemoAccess,WriteBack,Jjump,JALjump,jumpAddress);
  signal current_state : state;
  signal opcode  : std_logic_vector(5 downto 0);
  signal func : std_logic_vector(5 downto 0);
  

begin          --RTL

  opcode <= IR_32(31 downto 26);
  func <= IR_32(5 downto 0);
  
P1:  process(CLK,reset,current_state,opcode)

begin
  if reset ='1' then
    current_state <= IF1;
    MemRead <= '0';
    MemWrite <= '0';
  elsif rising_edge(CLK) then
   -- default values

    PCWrite <= '0';
    PCWriteCond <='0';
    loD <= '0';
    IRWrite <= '0';
    RegDst <= "00";
    mem2reg <="00";
    RegWrite <= '0';
    ALUSrcA  <= "00";
    ALUSrcB  <= "00";
    ALUcode <= ALU_ARITH & ALU_ADD;
    PCSource <= "00";
    signExtend <= '0';
    MemRead <= '0';
    MemWrite <= '0';
              
    case current_state is
     when IF1 =>
        loD <= '0';                 
        MemRead <= '1';
        current_state <= onecycle;

     when onecycle =>                   --this is just a one cycle to enalbe
       IRWrite <= '1';                  -- IRWrite so next cycle I write IR
       current_state <= IF2;            -- AND when decoding I have it ready!!
                                         -- 
     when IF2 =>
       --IRWrite <= '1';                  --too late here !!! 
       ALUSrcA <= "00";
       ALUSrcB <= "01";
       ALUcode <= ALU_ARITH & ALU_ADD;
       loD <= '0';
       PCWrite <= '1';
       PCSource <= "00";
       current_state <= IDecode;

     when IDecode =>
       ALUSrcA <= "00";
       ALUSrcB <= "11";
       signExtend <= '1';
       ALUcode <= ALU_ARITH & ALU_ADD;
       if opcode = OP_LW or opcode = OP_SW then
         current_state <= Addrcomp ;
       elsif opcode = OP_BEQ then
         current_state <= Branch;
       elsif opcode = OP_J then
         current_state <= Jjump;
       elsif opcode = OP_JAL then
         current_state <= JALjump;
         
       elsif opcode = "000000" and func = FUNCT_JR then
         current_state <= JumpAddress;
         else
           current_state <= Execute;
       end if;

     when Execute =>
 if opcode= "000000" then
   
       if func = FUNCT_ADDU then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
         ALUcode <= ALU_ARITH & ALU_ADDU;
       elsif func = FUNCT_SUBU then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
         ALUcode <= ALU_ARITH & ALU_SUBU;
       elsif func = FUNCT_AND then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
          RegDst <= "11";
         ALUcode <= ALU_LOGIC & ALU_AND;
       elsif func = FUNCT_OR then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
         AlUcode <= ALU_LOGIC & ALU_OR;
       elsif func = FUNCT_XOR then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
         AlUcode <= ALU_LOGIC & ALU_XOR;
       elsif func = FUNCT_NOR then
         ALUSrcA <= "01";
         ALUSrcB <= "00";
         AlUcode <= ALU_LOGIC & ALU_NOR;
       elsif func = FUNCT_SLL  then
         ALUSrcA <= "10";
         ALUSrcB <= "00";
         ALUcode <= ALU_SHIFT & ALU_SLL;
       elsif func = FUNCT_SRL then
         ALUSrcA <= "10";
         ALUSrcB <= "00";
         ALUcode <= ALU_SHIFT & ALU_SRL;      
       end if;
         
   elsif opcode = OP_ANDI then
     ALUSrcA <= "01";
     ALUSrcB <= "10";
     ALUcode <= ALU_LOGIC & ALU_AND;

   elsif opcode = OP_ORI then
     ALUSrcA <= "01";
     ALUSrcB <= "10";
     ALUcode <= ALU_LOGIC & ALU_OR;

   elsif opcode = OP_XORI then
     ALUSrcA <= "01";
     ALUSrcB <= "10";
     ALUcode <= ALU_LOGIC & ALU_XOR;
   end if;
   current_state <= Execute2;
         
   when Execute2 =>
    RegWrite <= '1';
    if opcode = "000000" then
      RegDst <= "11";
                else
                  RegDst <= "00";
                end if;
       current_state <= IF1;

   when Branch =>
      PCWriteCond <= '1';
      ALUSrcA <= "01";
      ALUSrcB <= "00";
      ALUcode <= ALU_ARITH & ALU_SUB;-- THE Z FLAGO WILL BE ON IF EQUAL!!
      PCSource <= "01";
      current_state <= IF1;
      
   when Jjump =>
      PCSource <= "11";
      PCWrite <= '1';
      current_state <= IF1;
      
     when JALjump =>
      PCSource <= "11";
      PCWrite <= '1';
      RegWrite <= '1';
      RegDst <= "01";
      mem2reg <= "01";
      current_state <= IF1;
      -- faltan cosas
   when jumpAddress =>
      PCSource <=  "10";
      PCWrite <= '1';
      current_state <= IF1;

   when Addrcomp =>
      ALUSrcA <= "01";           --prepare for a load into registers
      ALUSrcB <= "10";
      signExtend <= '1';
      ALUcode <= ALU_ARITH & ALU_ADD;
      current_state <= MemoAccess;

   when MemoAccess =>
      loD <= '1';
      if opcode = OP_SW then            --write to memory
        MemWrite <= '1';
        current_state <= IF1;
        else
          MemRead <= '1';
          ALUSrcA <= "01";
          ALUSrcB <= "10";              -- to calculate the address
          ALUcode <= ALU_ARITH & ALU_ADD;
          signExtend <= '1';
          current_state <= WriteBack;
        end if;
     when WriteBack =>
          RegDst <= "00";
          mem2reg <= "11";
          loD <= '1';
          RegWrite <= '1';
          current_state <= IF1;
        when others =>
        current_state <= IF1;
      end case;
  end if;

end process P1;
end RTL ;








