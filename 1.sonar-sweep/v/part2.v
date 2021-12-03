module solver (
    input clk,
    input enable,
    input reset,
    input [31:0] value,
    output reg [31:0] solution
);

reg [31:0] prev [3];

always @(posedge clk) begin
    if (reset) begin
        prev[0] <= ~0;
        prev[1] <= ~0;
        prev[2] <= ~0;
        solution <= 0;
    end else if (enable) begin
        if (value > prev[0]) begin
            solution <= solution + 1;
        end
        prev[0] <= prev[1];
        prev[1] <= prev[2];
        prev[2] <= value;
    end
end

endmodule
