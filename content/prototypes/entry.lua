print("hello from entry.lua!")

data:add({
    {
        name = "PrototypeOne",
        components =
        {
            {
                name = "PrintComponent",
                string = "Hello World!",
            }
        }
    },
    {
        name = "PrototypeTwo",
        components =
        {
            {
                name = "PrintTickComponent",
            }
        }
    }
})