module solver (
    input clk,
    input enable,
    input [1:0] directrion,
    input [31:0] value,
    output [31:0] solution
);

reg [31:0] position_x;
reg [31:0] position_y;

assign solution = position_x * position_y;

always @(posedge clk) begin
    if (enable) begin
        case (directrion)
            2'b00: begin // Forward
                position_x <= position_x + value;
            end
            2'b01: begin // Up
                position_y <= position_y - value;
            end
            2'b10: begin // Down
                position_y <= position_y + value;
            end
            2'b11: begin // Reset
                position_x <= 0;
                position_y <= 0;
            end
        endcase
    end
end

endmodule
