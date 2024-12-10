module PRegMemory #(
    parameter DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  ALUResultM,
    input   logic [DATA_WIDTH-1:0]  DMRd,
    input   logic [4:0]             RdM,
    input   logic [DATA_WIDTH-1:0]  PCPlus4M,
    input   logic                   clk,
    input   logic                   rst,
    input   logic                   mem_stall,    // New signal for memory stalls
    output  logic [4:0]             RdW,
    output  logic [DATA_WIDTH-1:0]  ALUResultW,
    output  logic [DATA_WIDTH-1:0]  ReadDataW,
    output  logic [DATA_WIDTH-1:0]  PCPlus4W,
    input   logic                   RegWriteM,
    input   logic [1:0]             ResultSrcM,
    output  logic                   RegWriteW,
    output  logic [1:0]             ResultSrcW
);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            ALUResultW <= 32'b0;
            ReadDataW  <= 32'b0;
            RdW        <= 5'b0;
            PCPlus4W   <= 32'b0;
            RegWriteW  <= 1'b0;
            ResultSrcW <= 2'b0;
        end else if (!mem_stall) begin  // Only update when not stalled
            ALUResultW <= ALUResultM;
            ReadDataW  <= DMRd;
            RdW        <= RdM;
            PCPlus4W   <= PCPlus4M;
            RegWriteW  <= RegWriteM;
            ResultSrcW <= ResultSrcM;
        end
    end

endmodule
