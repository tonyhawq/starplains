-- this file is required to be here but other folder structure
-- is not regulated

print("hello from entry.lua!")

data:add({
    {
        name = "PrototypeOne",
        components =
        {
            Print = {
                string = "Hello World!",
            }
        }
    },
    {
        name = "PrototypeTwo",
        components =
        {
            PrintTick = {}
        }
    }
})