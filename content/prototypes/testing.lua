data:add({
    {
        name = "Item",
        components =
        {
            Physics = {},
            Draggable = {},
            Item = {}
        }
    }
})
data:add({
    data:inherit{
        parent = "Item",
        name = "Skub",
        components =
        {
            Food = {
                nutriment = 10,
                taste = {"Skub"}
            }
        }
    }
})