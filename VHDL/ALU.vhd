library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.MUPS_pkg.all;

entity ALU is
  port (
    A, B   : in  std_logic_vector(31 downto 0);
    R      : out std_logic_vector(31 downto 0);
    ALU_Op : in  std_logic_vector(3 downto 0);
    Z, V   : out std_logic);
end ALU;


architecture combinational of ALU is

  signal R_Shift   : std_logic_vector(31 downto 0);
  signal R_Arith   : std_logic_vector(31 downto 0);
  signal R_Logic   : std_logic_vector(31 downto 0);
  signal R_Compare : std_logic_vector(31 downto 0);

  alias Op_Group : std_logic_vector(1 downto 0) is ALU_Op(3 downto 2);
  alias Op       : std_logic_vector(1 downto 0) is ALU_Op(1 downto 0);

  signal Cout : std_logic;
  
begin

  -- Add code here that performs the shift operations
  -- Shift functions are available in numeric_std 
  Shift : process(A, B, Op)
    variable nshifts : integer range 31 downto 0; -- num of shifts for 5 bit num 
  begin
    nshifts := to_integer(unsigned (A(4 downto 0)));

    case Op is
      when ALU_SLL =>
        R_Shift <= std_logic_vector( shift_left(unsigned(B),nshifts));
      when ALU_SRL =>
        R_Shift <= std_logic_vector(shift_right(unsigned(B),nshifts));
      when ALU_SRA =>
        R_Shift <= std_logic_vector(shift_right(signed(B),nshifts));
        --this will give back a signed signal meaning the replicate of the sign bit
      when others =>
        R_Shift <= (others => 'X');
    end case;
  end process;

  -- Add code here to implement ADD, ADDU, SUB and SUBU
  -- Remember that:
  -- A - B = A + not(B) + 1
  -- You will only need ONE adder to implement all four
  -- operations. If you use more than one you will have
  -- to change the code to get accepted.
  -- This process should also generate the Z and V flags
  -- For ADDU and SUBU overflow is ignored, V = 0
  -- This process should also generate a carry out from
  -- the adder. 
  Arith : process(A, B, Op, Op_Group)
    variable B_aux : std_logic_vector (31 downto 0);  
    variable C_in : std_logic_vector (31 downto 0);
    variable R_33 : std_logic_vector(32 downto 0);  --temporary the result+the
                                                    --carry bit, 33 bits
    begin

     C_in := x"00000000";
     
     case Op is
      when ALU_ADD => B_aux := B;
                      C_in := x"00000000";
      when ALU_ADDU => B_aux := B;
                      C_in := x"00000000";
      when ALU_SUB => B_aux :=not(B);
                      C_in := "00000000000000000000000000000001";        --this is for 2's complement
      when ALU_SUBU=> B_aux :=not(B);
                       C_in := "00000000000000000000000000000001";
       when others => R_33 := x"00000000"& "0";
     end case;
     R_33 := std_logic_vector(unsigned("0"&A)+unsigned(B_aux)+unsigned(C_in));
     --the over flow __
       V <= '0';
     if Op_Group = ALU_ARITH then
       if Op = ALU_ADD then
            if ((A(31) = B(31)) and (R_33(31) /= A(31))) then V <= '1';
                  end if;
        elsif
         Op = ALU_SUB then
             if ((A(31) /= B(31)) and (R_33(31) = B(31))) then V <= '1';
             end if;
         end if;
     end if;
                  
                 
                 
     Cout <= R_33(32);
     R_Arith <= R_33(31 downto 0);
     if ((Op_Group = ALU_ARITH) and (R_33(31 downto 0) = x"00000000")) then
            Z <= '1';
     else
       Z <= '0' ;
       end if;

     end process;

   -- This process should implement the logic operations
   -- AND, OR,  NOR, XOR
   Logic : process(A, B, Op)
   begin
     case Op is
        when ALU_AND => R_Logic <= A and B ;
        when ALU_OR => R_Logic <= A or B;
        when ALU_XOR => R_Logic <= A xor B;
        when ALU_NOR => R_Logic <= A nor B;
        when others =>  R_Logic <= (others => 'X');
      end case;
   end process;

   -- This process should implement the compare functions-   -- SLT and SLTU. In both cases a subtraction A-B is perform
   -- in the Arith process. The sign bits of the operands and
   -- the result are for the SLT operation. The carry is useful
   -- for the SLTU operation
   Compare : process(Cout, A(31), B(31), R_Arith(31), Op)
   begin
     R_Compare <= x"00000000";
     case Op is
     when ALU_SLT=>
         R_compare(0) <= R_Arith(31) xor ((not A(31) and B(31) and R_Arith(31)) or (A(31) and not(B(31)) and not (R_Arith(31))));
     when ALU_SLTU=>
       R_Compare(0) <= not(Cout);
       when others => R_Compare <= (others => 'X');
     end case;
    
   end process;

   -- This process is complete! It implements a 4-1 MUX 
   OMux : process(Op_Group, R_Shift, R_Arith, R_Logic, R_Compare)
   begin
     case Op_Group is
       when ALU_ARITH =>
         R <= R_Arith;
      when ALU_LOGIC =>
        R <= R_Logic;
      when ALU_SHIFT =>
        R <= R_Shift;
      when ALU_COMPARE =>
        R <= R_Compare;
      when others =>
        R <= (others => 'X');
    end case;
  end process;

end combinational;

