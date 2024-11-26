module ALU #(
    parameter DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  SrcA,
    input   logic [DATA_WIDTH-1:0]  SrcB,
    input   logic [3:0]             ALUControl,
    output  logic [DATA_WIDTH-1:0]  ALUResult,
    output  logic                   zero
);

    logic [DATA_WIDTH-1:0] add, sub, Opand, Opor, Opxor, slt, sltu, shift_left, shift_right, shift_arith;

    always_comb begin
        zero = 0;
        add = SrcA + SrcB;
        sub = SrcA - SrcB;
        Opand = SrcA & SrcB;
        Opor = SrcA | SrcB;
        Opxor = SrcA ^ SrcB;
        slt = (SrcA < SrcB) ? {{(DATA_WIDTH-1){1'b0}}, 1'b1} : {DATA_WIDTH{1'b0}};
        sltu = ($unsigned(SrcA) < $unsigned(SrcB)) ? {{(DATA_WIDTH-1){1'b0}}, 1'b1} : {DATA_WIDTH{1'b0}};
        shift_left = SrcA << SrcB[4:0];
        shift_right = SrcA >> SrcB[4:0];
        shift_arith = $signed(SrcA) >>> SrcB[4:0];

        case (ALUControl)
            4'b0000: ALUResult = add;
            4'b1000: ALUResult = sub;
            4'b0010: ALUResult = Opand;
            4'b0011: ALUResult = Opor;
            4'b0100: ALUResult = Opxor;
            4'b0101: ALUResult = slt;
            4'b0111: ALUResult = sltu;
            4'b0110: ALUResult = shift_left;
            4'b1110: ALUResult = shift_right;
            4'b1100: ALUResult = shift_arith;
            default: ALUResult = {DATA_WIDTH{1'b0}};
        endcase

        zero = (ALUResult == {DATA_WIDTH{1'b0}});
    end

endmodule
