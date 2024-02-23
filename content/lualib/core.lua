
---@diagnostic disable-next-line: lowercase-global
data = {
    internal = {}

}

function data.add(self, tab)
    if type(tab) ~= "table" then
        error("data:add() expects table argument, got "..type(tab))
        return
    end
    for k, ptype in pairs(tab) do
        if type(ptype) ~= "table" then
            error("data:add() expects a table of tables, got "..type(tab).." as argument "..k)
            return
        end
        self.internal[ptype.name] = ptype
    end
end