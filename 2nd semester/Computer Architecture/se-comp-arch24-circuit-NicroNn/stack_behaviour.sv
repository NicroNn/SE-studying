module stack_behaviour_normal(
    inout wire[3:0] IO_DATA,
    input wire RESET,
    input wire CLK,
    input wire[1:0] COMMAND,
    input wire[2:0] INDEX
    );

    reg [3:0] mas[4:0];
    integer i;
    reg[3:0] res;
    reg unsigned[2:0] index, index2, get_index, temp;
    reg rw;

    always @ (posedge RESET) begin
        index = 0;
        index2 = 4;
        rw = 0;
        res = 0;
        for (i = 0; i < 5; i+=1) begin
            mas[i] = 4'b0000;
        end
    end

    always @ (negedge CLK) begin
        rw = 0;
    end

    always @ (posedge CLK or negedge RESET) begin
        if (CLK == 1 & RESET == 0) begin
            if (COMMAND == 2'b01) begin
                rw = 0;
                for (i = 0; i < 5; i += 1) begin
                    if (index == i) begin
                        mas[i] = IO_DATA;
                    end
                end
                index2 += 1;
                index += 1;
                if (index == 5) begin
                    index = 0;
                end
                if (index2 == 5) begin
                    index2 = 0;
                end
            end else if (COMMAND == 2'b10) begin
                rw = 1;
                res = mas[index2];
                if (index != 0) begin
                    index -= 1;
                end else begin
                    index = 4;
                end
                if (index2 != 0) begin
                    index2 -= 1;
                end else begin
                    index2 = 4;
                end
            end else if (COMMAND == 2'b11) begin
                rw = 1;
                temp = INDEX;
                if (temp > 4) begin
                    temp -= 5;
                end
                if (index2 >= temp) begin
                    get_index = index2 - temp;
                end else begin
                    get_index = 5 - (temp - index2);
                end
                res = mas[get_index];
            end
        end
    end

    assign IO_DATA = (rw) ? res : 4'bZZZZ;
endmodule