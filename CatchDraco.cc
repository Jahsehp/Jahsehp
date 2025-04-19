--[[
made by : catchDraco
Telegram : CatchDraco
]]

local plr = game:GetService("Players").LocalPlayer
local chr = plr.Character or plr.CharacterAdded:Wait()
local hum = chr:WaitForChild("Humanoid")
local root = chr:WaitForChild("HumanoidRootPart")
local uis = game:GetService("UserInputService")
local tweenService = game:GetService("TweenService")
local camera = workspace.CurrentCamera
local mouse = plr:GetMouse()

local multipliers = {
    walkSpeed = 2,
    jumpPower = 2,
}

local keybinds = {
    speed = Enum.KeyCode.LeftShift,
    jump = Enum.KeyCode.Space,
}

local booleans = {
    infiniteStamina = true,
    speedEnabled = false,
    jumpEnabled = false,
}

local tag = "8BallLag"

local notification = function(title, text)
    game.StarterGui:SetCore("SendNotification", {
        Title = title,
        Text = text,
        Duration = 5,
        -- Note: SetCore notifications do not support custom colors.
        -- For black background and purple text, use a custom ScreenGui.
    })
end

local oldWalkSpeed = hum.WalkSpeed
local oldJumpPower = hum.JumpPower

uis.InputBegan:Connect(function(key, GPE)
    if GPE then return end

    if key == keybinds.speed then
        booleans.speedEnabled = true
        hum.WalkSpeed = oldWalkSpeed * multipliers.walkSpeed
        notification(tag, "Speed Enabled")
    elseif key == keybinds.jump then
        booleans.jumpEnabled = true
        hum.JumpPower = oldJumpPower * multipliers.jumpPower
        notification(tag, "Jump Enabled")
    end
end)

uis.InputEnded:Connect(function(key, GPE)
    if GPE then return end

    if key == keybinds.speed then
        booleans.speedEnabled = false
        hum.WalkSpeed = oldWalkSpeed
        notification(tag, "Speed Disabled")
    elseif key == keybinds.jump then
        booleans.jumpEnabled = false
        hum.JumpPower = oldJumpPower
        notification(tag, "Jump Disabled")
    end
end)

hum.Died:Connect(function()
    hum.WalkSpeed = oldWalkSpeed
    hum.JumpPower = oldJumpPower
end)

if booleans.infiniteStamina then
    hum:SetStateEnabled(Enum.HumanoidStateType.RunningNoPhysics, false)
end

notification(tag, "Loaded")
