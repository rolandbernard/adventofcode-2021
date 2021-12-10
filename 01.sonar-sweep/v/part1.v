module solver (
    input clk,
    input enable,
    input reset,
    input [31:0] value,
    output reg [31:0] solution
);

reg [31:0] prev;

always @(posedge clk) begin
    if (reset) begin
        prev <= ~0;
        solution <= 0;
    end else if (enable) begin
        if (value > prev) begin
            solution <= solution + 1;
        end
        prev <= value;
    end
end

endmodule
