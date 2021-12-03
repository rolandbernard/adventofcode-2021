module solver (
    input clk,
    input enable,
    input reset,
    input [11:0] value,
    output [31:0] solution
);

reg [31:0] count;
reg [31:0] counts [12];
wire [11:0] counted;

for (genvar i = 0; i < 12; i = i + 1) begin
    assign counted[i] = counts[i] > count ? 1 : 0;
end

assign solution = {20'b0, counted} * {20'b0, ~counted};

always @(posedge clk) begin
    if (reset) begin
        count <= 0;
        for (integer i = 0; i < 12; i = i + 1) begin
            counts[i] <= 0;
        end
    end else if (enable) begin
        for (integer  i = 0; i < 12; i = i + 1) begin
            counts[i] <= counts[i] + {30'b0, value[i], 1'b0};
        end
        count <= count + 1;
    end
end

endmodule
