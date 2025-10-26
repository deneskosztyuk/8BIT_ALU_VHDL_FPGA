-- VHDL Program to simulate an ALU
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY ALU IS
    PORT (
        clk      : in  STD_LOGIC;                    -- Clock input
		  S        : in  STD_LOGIC_VECTOR(9 downto 0); -- Input from switches
		  reset	  : in  STD_LOGIC; 						  -- Reset input
        E        : in  STD_LOGIC_VECTOR(7 downto 0); -- Input E
        carryIn  : in  STD_LOGIC;                    -- Carry input
        OpCode   : in  STD_LOGIC_VECTOR(3 DOWNTO 0)  -- Operation code
		  carryOut : out STD_LOGIC;                    -- Carry output
		  HEX0	  : out STD_LOGIC_VECTOR(6 downto 0); -- HEX Display output
		  Z        : out STD_LOGIC_VECTOR(7 downto 0); -- Output Z
    );
END ALU;

ARCHITECTURE Behavioral OF ALU IS
    -- Signal declarations
    signal result : std_logic_VECTOR(8 downto 0) := "000000000"; 	   -- Result buffer
    signal A      : STD_LOGIC_VECTOR(8 downto 0) := "000000000";     -- Buffer A
    signal B      : STD_LOGIC_VECTOR(8 downto 0) := "000000000";     -- Buffer B
	 signal OpCode : STD_LOGIC_VECTOR(3 downto 0) := (others => '0'); -- OpCode
	 
	 -- Binary to 7-segment decoder function for common anode HEX display
    FUNCTION bin_to_hex(seg : STD_LOGIC_VECTOR(3 downto 0)) RETURN STD_LOGIC_VECTOR IS
        VARIABLE display : STD_LOGIC_VECTOR(6 downto 0);
BEGIN
    CASE seg IS
		when "0000" => display := "0000001"; -- 0
		when "0001" => display := "1001111"; -- 1
		when "0010" => display := "0010010"; -- 2
		when "0011" => display := "0000110"; -- 3
		when "0100" => display := "1001100"; -- 4
		when "0101" => display := "0100100"; -- 5
		when "0110" => display := "0100000"; -- 6
		when "0111" => display := "0001111"; -- 7
		when "1000" => display := "0000000"; -- 8
		when "1001" => display := "0000100"; -- 9
		when "1010" => display := "0001000"; -- A
		when "1011" => display := "1100000"; -- B
		when "1100" => display := "0110001"; -- C
		when "1101" => display := "1000010"; -- D
		when "1110" => display := "0110000"; -- E
		when "1111" => display := "0111000"; -- F
		when OTHERS => display := "1111111"; -- Display off (for undefined input)
	END CASE;
RETURN display;
END bin_to_hex;
	 

BEGIN    
    PROCESS (clk)
    BEGIN
        if rising_edge(clk) then
            if reset = '1' then  -- If reset is pressed, perform reset
                -- Reset logic to clear all registers
                A <= (others => '0');
                B <= (others => '0');
                result <= (others => '0');
                -- Additional reset logic as needed
            else
                -- OpCode Mode: S9 = '1', Load OpCode
                -- Execute Mode: S9 = '0', Execute OpCode and output result
                if S(9) = '1' then
                    OpCode <= S(3 downto 0);  -- Load the opcode from switches
                else
                    -- Execute mode, perform the operation based on the OpCode
						  -- '0'000 Arithmetic
							case OpCode is
								 when "0000" => -- Load A
									  A(7 downto 0) <= E;
								 when "0001" => -- Increment A
									  result <= A + 1;
								 when "0010" => -- Decrement A
									  result <= A - 1;
								 when "0011" => -- Load B
									  B(7 downto 0) <= E;
								 when "0100" => -- Increment B
									  result <= B + 1;
								 when "0101" => -- Decrement B
									  result <= B - 1;
								 when "0110" => -- Add A and B
									  result <= A + B;
								 when "0111" => -- Add A and B with Carry bit (C/in)
									  result <= A + B + carryIn;
								 
								 -- '1'000 Logic
								 when "1000" => -- Complement A
									  result <= not A;
								 when "1001" => -- Complement B
									  result <= not B;
								 when "1010" => -- AND
									  result <= A and B;
								 when "1011" => -- OR
									  result <= A or B;
								 when "1100" => -- NAND
									  result <= not (A and B);
								 when "1101" => -- NOR
									  result <= not (A or B);
								 when "1110" => -- XOR
									  result <= A xor B;
								 when "1111" => -- XNOR
									  result <= not (A xor B);
								 WHEN OTHERS => -- handles undefined input
									  result <= (others => '0');
							End case;
						
					-- Check if result exceeds 255 (11111111 in binary)
					if result > "11111111" then
						 carryOut <= result(8);
						 Z <= result(7 downto 0);
					else
						 carryOut <= result(8);
						 Z <= result(7 downto 0);
					end if;
        
        end if;
    END PROCESS;
END Behavioral;

