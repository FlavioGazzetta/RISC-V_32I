module PRegFetch #(
    parameter DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  instr,
    input   logic [DATA_WIDTH-1:0]  PCf,
    input   logic [DATA_WIDTH-1:0]  PCPlus4F,
    input   logic                   clk,
    //input   logic                   FlushD,
    input   logic                   rst,         // Reset signal
    output  logic [DATA_WIDTH-1:0]  PCPlus4D,
    output  logic [DATA_WIDTH-1:0]  PCd,
    output  logic [DATA_WIDTH-1:0]  InstrD
);

    // Sequential logic for writing and output generation
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            // Reset or flush: Set outputs to default values
            InstrD   <= 32'b0;
            PCd      <= 32'b0;
            PCPlus4D <= 32'b0;
        end /* else if (FlushD) begin 
            InstrD   <= 32'b0;
            PCd      <= 32'b0;
            PCPlus4D <= 32'b0;
        end */ else begin
            // Normal operation: Assign inputs to outputs
            InstrD   <= instr;
            PCd      <= PCf;
            PCPlus4D <= PCPlus4F;
        end
    end

endmodule
