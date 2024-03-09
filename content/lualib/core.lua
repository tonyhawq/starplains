
---@diagnostic disable-next-line: lowercase-global
data = data or {
    internal = {},
    add = function (self, tab)
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
    end,
    inherit = function (self, tab)
        if not tab.parent then
            error("data:inherit() requires a parent to inherit from.")
            return
        end
        if not self.internal[tab.parent] then
            error("cannot inherit from \""..tab.parent.."\", no such parent exists")
            return
        end
        local result = self.internal[tab.parent]
        result.name = tab.name
        for name, override in pairs(tab.components) do
            result.components[name] = override
        end
        return result
    end
}