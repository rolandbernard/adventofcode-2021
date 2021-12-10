module solver (
    input clk,
    input reset,
    input insert,
    input advance,
    input [3:0] value,
    output [40:0] solution
);

reg [40:0] counts [9];

assign solution =
    counts[0] + counts[1] + counts[2]
    + counts[3] + counts[4] + counts[5]
    + counts[6] + counts[7] + counts[8];

always @(posedge clk) begin
    if (reset) begin
        for (integer i = 0; i < 9; i = i + 1) begin
            counts[i] <= 0;
        end
    end if (insert) begin
        counts[value] <= counts[value] + 1;
    end if (advance) begin
        for (integer i = 1; i < 7; i = i + 1) begin
            counts[i - 1] <= counts[i];
        end
        counts[6] <= counts[7] + counts[0];
        counts[7] <= counts[8];
        counts[8] <= counts[0];
    end
end

endmodule
